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

static PyListObject* n_range_below(PyObject* self, PyObject* args) {

    int length, below, amount;

    if (!PyArg_ParseTuple(args, "iii", &length, &below, &amount)) {
        return NULL;
    }

    if (amount < 0) {
        PyGILState_STATE gstate = PyGILState_Ensure();
        PyErr_SetString(PyExc_ValueError, "Amount must be positive");
        PyGILState_Release(gstate);

        return NULL;
    }

    if (length > below) {
        PyGILState_STATE gstate = PyGILState_Ensure();
        PyErr_SetString(PyExc_ValueError, "Length must be smaller than 'below', because this method will return a non-repeated values.");
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
        memset(array, length+1, length * sizeof(int));
        PyListObject* sublist = (PyListObject*) PyList_New((Py_ssize_t)length);

        int pos = 0;

        while (1) {
            
            int insert = 1;
            
            if (!generate_rdrand64_below(&randf, below+1)) {
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
                    array[pos++] = (int) randf;
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

static PyListObject* range_below(PyObject* self, PyObject* args) {

    int length, below;

    if (!PyArg_ParseTuple(args, "ii", &length, &below)) {
        return NULL;
    }

    if (length > below) {
        PyGILState_STATE gstate = PyGILState_Ensure();
        PyErr_SetString(PyExc_ValueError, "Length must be smaller than 'below', because this method will return a non-repeated values.");
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
    memset(array, length+1, length * sizeof(int));

    int pos = 0;

    while (1) {
        
        int insert = 1;
        
        if (!generate_rdrand64_below(&randf, below+1)) {
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
                array[pos++] = (int) randf;
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

static PyListObject* range(PyObject* self, PyObject* args, PyObject* kwargs) {

    int length;
    int boundary = 90;

    char* keywords[] = {"length", "boundary", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i|i", keywords, &length, &boundary)) {
        return NULL;
    }

    if (length > boundary) {

        char exception_text[256];
        sprintf(exception_text, "Lenght must be in the following range 0-%d.\n", abs(boundary));

        PyGILState_STATE gstate = PyGILState_Ensure();
        PyErr_SetString(PyExc_ValueError, exception_text);
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
    
    // int array[91] = { 0 };
    int* array = (int*) malloc(boundary * sizeof(int));
    memset(array, 0, boundary * sizeof(int));
    
    int pos = 0;

    while (1) {
        
        int insert = 1;
        
        if (!generate_rdrand64_boundary(&randf, boundary)) {
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

static PyObject* rdseed(PyObject* self) {

    uint64_t retorno = 0;
    generate_rdseed(&retorno);

    return (PyObject*) PyLong_FromLong(retorno);
}

static PyMethodDef methods[] = {
    {"range", (PyCFunction)range, METH_VARARGS | METH_KEYWORDS, range__doc__},
    {"randint", (PyCFunction)randint, METH_VARARGS, randint__doc__},
    {"range_below", (PyCFunction)range_below, METH_VARARGS, range_below__doc__},
    {"n_range_below", (PyCFunction)n_range_below, METH_VARARGS, n_range_below__doc__},
    {"is_rdrand_supported", (PyCFunction)is_rdrand_supported, METH_NOARGS, is_rdrand_supported__doc__},
    {"is_rdseed_supported", (PyCFunction)is_rdseed_supported, METH_NOARGS, is_rdseed_supported__doc__},
    {"rdseed", (PyCFunction)rdseed, METH_NOARGS, "Return a int64 long using rdseed cpu instruction."},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef Module = {
    PyModuleDef_HEAD_INIT,
    "_rdrand",
    rdrand__doc__,
    -1,
    methods
};

PyMODINIT_FUNC PyInit__rdrand(void) {
    
    /* Check rdrand/rdseed compatibiltiy before initialize the module */
    if (rdrand_check_support() != 1 || rdseed_check_support() != 1) {

        PyGILState_STATE gstate = PyGILState_Ensure();
        PyErr_SetString(PyExc_ImportError, "This CPU does not support the rdrand/rdseed instruction.\n");
        PyGILState_Release(gstate);

        return NULL;
    }

    return PyModule_Create(&Module);
}

// int main(int argc, char** argv) {
//     wchar_t *program = Py_DecodeLocale(argv[0], NULL);
    
//     if (program == NULL) {
//         fprintf(stderr, "Fatal error: cannot decode argv[0].\n");
//         exit(1);
//     }

//     /* Add a built-in module, before Py_Initialize */
//     if (PyImport_AppendInittab("rdrand", PyInit_rdrand) == -1) {
//         fprintf(stderr, "Error: could not extend in-built modules table.\n");
//         exit(1);
//     }

//     Py_SetProgramName(program);

//     /* Initialize the Python interpreter */
//     Py_Initialize();

//     PyObject *pmodule = PyImport_ImportModule("rdrand");
//     if (!pmodule) {
//         PyErr_Print();
//         fprintf(stderr, "Error: could not import module 'rdrand'.\n");
//     }

//     PyMem_RawFree(program);
//     return 0;
// }