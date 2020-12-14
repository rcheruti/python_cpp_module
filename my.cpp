
// #define PY_SSIZE_T_CLEAN
#include <Python.h>

#include "src/Pessoa.cpp"
#include "src/Database.cpp"

char lf[] = "\n";

// -------------------------------

int installModule(PyObject* module, PyTypeObject* type, char const* nome) {
    if (PyType_Ready( type ) < 0) {
        printf("Estrutura de Pessoa nao esta pronta para carregar!!!\n");
        return -1;
    }
    Py_INCREF( type );
    PyModule_AddObject(module, nome, (PyObject *)type );
    return 0;
}

// -------------------------------
// configurações dos módulos para integrão com Python

static PyMethodDef my_methods[] = {
    // Terminate the array with an object containing nulls.
    { NULL, NULL, 0, NULL }
};
// inicialização do Módulo Python:
static struct PyModuleDef moduledef = {
    PyModuleDef_HEAD_INIT,
    "my",                /* m_name */
    "This is a module",  /* m_doc */
    -1,                  /* m_size */
    my_methods,          /* m_methods */
    NULL,                /* m_reload */
    NULL,                /* m_traverse */
    NULL,                /* m_clear */
    NULL,                /* m_free */
};
#ifndef PyMODINIT_FUNC	/* declarations for DLL import/export */
#define PyMODINIT_FUNC void
#endif
PyMODINIT_FUNC PyInit_my() {
    PyObject* module = PyModule_Create(&moduledef);
    installModule( module, &DatabaseType, "Database" );
    installModule( module, &PessoaType, "Pessoa" );
    return module;
}