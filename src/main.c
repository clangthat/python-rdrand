#define PYW_SSIZE_T_CLEAN
#include <Python.h>
#include <stdio.h>
#include <stdlib.h>
#include "include/common.h"


static PyListObject* generate_range(PyObject* self, PyObject* args) {

    int length;
    
    if (!PyArg_ParseTuple(args, "i", &length)) {
        return NULL;
    }

    int randf;
    // char* output = malloc(FIXED_SIZE);
    PyListObject* output = (PyListObject*) PyList_New((Py_ssize_t)length);
    int array[91] = { 0 };
    int pos = 0;



    //memset(output, 0, FIXED_SIZE);

    if (length > 90) {
        printf("Length must be in the following range: 1-90. %d given.\n", length);
        return NULL;
    }

    while (1) {
        
        int insert = 1;
        
        if (!generate_rdrand64(&randf)) {
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

static PyMethodDef AllModules[] = {
    {"generate_range", (PyCFunction)generate_range, METH_VARARGS, "Return a list of random numbers."},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef Module = {
    PyModuleDef_HEAD_INIT,
    "Module",
    "generate_range module",
    -1,
    AllModules
};

PyMODINIT_FUNC PyInit_rdrand(void) {
    return PyModule_Create(&Module);
}