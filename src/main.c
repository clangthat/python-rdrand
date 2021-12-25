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

static PyListObject* generate_n_range_bellow(PyObject* self, PyObject* args) {

    int length, bellow, amount;

    if (!PyArg_ParseTuple(args, "iii", &length, &bellow, &amount)) {
        return NULL;
    }

    if (amount < 0) {
        PyGILState_STATE gstate = PyGILState_Ensure();
        PyErr_SetString(PyExc_ValueError, "Amount must be positive");
        PyGILState_Release(gstate);

        return NULL;
    }

    if (length > bellow) {
        PyGILState_STATE gstate = PyGILState_Ensure();
        PyErr_SetString(PyExc_ValueError, "Length must be smaller than 'bellow', because this method will return a non-repeated values.");
        PyGILState_Release(gstate);

        return NULL;
    }

    if (length < 0) {

        PyGILState_STATE gstate = PyGILState_Ensure();
        PyErr_SetString(PyExc_ValueError, "Length must be positive.");
        PyGILState_Release(gstate);

        return NULL;
    }

    int randf;
    int* array = malloc(length * sizeof(int));

    PyListObject* output = (PyListObject*) PyList_New((Py_ssize_t)amount);

    for (int i = 0; i < amount; i++) {
        memset(array, 0, length * sizeof(int));
        PyListObject* sublist = (PyListObject*) PyList_New((Py_ssize_t)length);

        int pos = 0;

        while (1) {
            
            int insert = 1;
            
            if (!generate_rdrand64_bellow(&randf, bellow)) {
                for (int j = 0; j < length; j++) {
                    if (array[j] == (int) randf) {
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

        for (int j = 0; j < length; j++) {
            PyList_SetItem((PyObject*) sublist, (Py_ssize_t) j, PyLong_FromLong(array[j]));
        }

        PyList_SetItem((PyObject*) output, (Py_ssize_t) i, (PyObject*) sublist);
        // PyList_Append(output, sublist);

    }

    free(array);
    return output;
}

static PyListObject* generate_range_bellow(PyObject* self, PyObject* args) {

    int length, bellow;

    if (!PyArg_ParseTuple(args, "ii", &length, &bellow)) {
        return NULL;
    }

    if (length > bellow) {
        PyGILState_STATE gstate = PyGILState_Ensure();
        PyErr_SetString(PyExc_ValueError, "Length must be smaller than 'bellow', because this method will return a non-repeated values.");
        PyGILState_Release(gstate);

        return NULL;
    }

    if (length < 0) {

        PyGILState_STATE gstate = PyGILState_Ensure();
        PyErr_SetString(PyExc_ValueError, "Length must be positive.");
        PyGILState_Release(gstate);

        return NULL;
    }

    int randf;
    PyListObject* output = (PyListObject*) PyList_New((Py_ssize_t)length);

    int* array = malloc(length * sizeof(int));
    memset(array, 0, length * sizeof(int));

    int pos = 0;

    while (1) {
        
        int insert = 1;
        
        if (!generate_rdrand64_bellow(&randf, bellow)) {
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

    free(array);
    return output;
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

static PyObject* is_rdrand_supported(PyObject* self) {
    if (rdrand_check_support() == 1)
        return (PyObject*)Py_True;
    return (PyObject*)Py_False;
}

static PyObject* is_rdseed_supported(PyObject* self) {
    if (rdseed_check_support() == 1)
        return (PyObject*)Py_True;
    return (PyObject*)Py_False;
}

static PyMethodDef methods[] = {
    {"generate_range", (PyCFunction)generate_range, METH_VARARGS, generate_range__doc__},
    {"randint", (PyCFunction)randint, METH_VARARGS, randint__doc__},
    {"generate_range_bellow", (PyCFunction)generate_range_bellow, METH_VARARGS, generate_range_bellow__doc__},
    {"generate_n_range_bellow", (PyCFunction)generate_n_range_bellow, METH_VARARGS, generate_n_range_bellow__doc__},
    {"is_rdrand_supported", (PyCFunction)is_rdrand_supported, METH_NOARGS, is_rdrand_supported__doc__},
    {"is_rdseed_supported", (PyCFunction)is_rdseed_supported, METH_NOARGS, is_rdseed_supported__doc__},
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