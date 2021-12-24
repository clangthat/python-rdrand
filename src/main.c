#define PYW_SSIZE_T_CLEAN
#include <Python.h>

#include "include/common.h"
#include "include/pydef.h"


static PyObject* randint(PyObject* self, PyObject *args) {

    int randf;
    int min, max;

    if (!PyArg_ParseTuple(args, "ii", &min, &max)) {
        return NULL;
    }

    if (min > max) {
        PyGILState_STATE gstate = PyGILState_Ensure();
        PyErr_SetString(PyExc_ValueError, "Minimum value is greater than max.\n");
        PyGILState_Release(gstate);

        return NULL;
    }

    if (min < 0 && max < 0) {
        PyGILState_STATE gstate = PyGILState_Ensure();
        PyErr_SetString(PyExc_ValueError, "Negative range isn't supported.");
        PyGILState_Release(gstate);

        return NULL;
    }

    max++;

    while (1) {
        if (!generate_rdrand64(&randf, max)) {

            if (randf >= min && randf <= max)
                break;

        } else {
            perror("Failed to get random value.");
            exit(2);
        }
    }

    // if (min < 0 && max < 0 && randf > 0)
    //     randf = ~randf + 1;

    return (PyObject*) PyLong_FromLong(randf);

}

static PyListObject* generate_range(PyObject* self, PyObject* args) {

    int length;
    
    if (!PyArg_ParseTuple(args, "i", &length)) {
        return NULL;
    }

    if (length > 90) {

        PyGILState_STATE gstate = PyGILState_Ensure();
        PyErr_SetString(PyExc_ValueError, "Lenght must be in the following range 0-90.\n");
        PyGILState_Release(gstate);

        return NULL;
    }

    if (length < 0) {
        PyGILState_STATE gstate = PyGILState_Ensure();
        PyErr_SetString(PyExc_ValueError, "length must be positive");
        PyGILState_Release(gstate);

        return NULL;
    }

    int randf;
    PyListObject* output = (PyListObject*) PyList_New((Py_ssize_t)length);
    
    int array[91] = { 0 };
    int pos = 0;

    while (1) {
        
        int insert = 1;
        
        if (!generate_rdrand64_90(&randf)) {
            for (int i = 0; i < length; i++) {
                if (array[i] == (int) randf) {
                    insert = 0;
                    break;
                }
            }

            if (pos == length) {
                break;
            }

            if (insert) {
                array[pos] = (int) randf;
                pos++;
            }
        } else {
            perror("Failed to get random value.");
            exit(2);
        }
    }

    for (int i = 0; i < length; i++) {
        PyList_SetItem((PyObject*) output, (Py_ssize_t) i, PyLong_FromLong(array[i]));
    }

    return output;
}


static PyMethodDef methods[] = {
    {"generate_range", (PyCFunction)generate_range, METH_VARARGS, generate_range__doc__},
    {"randint", (PyCFunction)randint, METH_VARARGS, randint__doc__},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef Module = {
    PyModuleDef_HEAD_INIT,
    "rdrand",
    "generate_range module",
    -1,
    methods
};

PyMODINIT_FUNC PyInit_rdrand(void) {
    return PyModule_Create(&Module);
}