
#ifdef MY_DATABASE
#else
#define MY_DATABASE

#include <Python.h>
#include <structmember.h>
#include <stdio.h>
#include <vector>
#include "Pessoa.cpp"

typedef struct {
    PyObject_HEAD
    std::vector<Pessoa*> itens;
} Database ;

static PyMemberDef Database_members[] = {
    {NULL}  /* Sentinel */
};

static PyObject* Database_save(Database* self, PyObject* args) {
    char *filename = NULL;
    if( !PyArg_ParseTuple(args, "s", &filename) ) return NULL;

    FILE* arq = fopen(filename, "w");
    fputs( "Nome;idade\n", arq);
    for(unsigned i = 0; i < self->itens.size(); i++) {
        Pessoa* item = self->itens.at( i );
        fputs( item->nome, arq );
        fputs( ";", arq );
        char numero[10];
        snprintf(numero, 10, "%d", item->idade );
        fputs( numero, arq );
        fputs( "\n", arq );
    }
    fclose( arq );

    Py_INCREF( self ); // necessario aumentar sempre que retornar a propria referencia
    return (PyObject*)self;
}
static PyObject* Database_add(Database* self, PyObject* args) {
    Pessoa* pessoa;
    if( !PyArg_ParseTuple(args, "O", &pessoa) ) return NULL;
    self->itens.push_back( pessoa );
    Py_INCREF( pessoa );
    Py_INCREF( self ); // necessario aumentar sempre que retornar a propria referencia
    return (PyObject*)self;
}
static PyObject* Database_remove(Database* self, PyObject* args) {
    int idx = 0;
    if( !PyArg_ParseTuple(args, "i", &idx) ) return NULL;
    Pessoa* pessoa = self->itens.at( idx );
    self->itens.erase( self->itens.begin() + idx );
    Py_DECREF( pessoa );
    Py_INCREF( self ); // necessario aumentar sempre que retornar a propria referencia
    return (PyObject*)self;
}



static PyMethodDef Database_methods[] = {
    {"save", (PyCFunction)Database_save, METH_VARARGS, "Gravar arquivo do Database.", },
    {"add", (PyCFunction)Database_add, METH_VARARGS, "Adicionar itens no DB.", },
    {"remove", (PyCFunction)Database_remove, METH_VARARGS, "Remover itens do DB.", },
    {NULL}  /* Sentinel */
};

// --------------------------------------
// Python integration

static void Database_dealloc(PyObject* selfObj) {
    Database* self = (Database*)selfObj;
    for(unsigned i = 0; i < self->itens.size(); i++) {
        Pessoa* pessoa = self->itens.at( i );
        Py_DECREF( pessoa ); // necessario retirar referencias aos objetos
    }
    Py_TYPE(self)->tp_free(self);
}
static PyObject* Database_new(PyTypeObject *type, PyObject *args, PyObject *kwds) {
    return (PyObject*) type->tp_alloc(type, 0);
}
static int Database_init(Database* self, PyObject* args, PyObject* kwds) {
    // nada aqui por enquanto
    return 0;
}

static PyTypeObject DatabaseType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "my.Database",             /* tp_name */
    sizeof(Database),          /* tp_basicsize */
    0,                         /* tp_itemsize */
    Database_dealloc,          /* tp_dealloc */
    0,                         /* tp_print */
    0,                         /* tp_getattr */
    0,                         /* tp_setattr */
    0,                         /* tp_compare */
    0,                         /* tp_repr */
    0,                         /* tp_as_number */
    0,                         /* tp_as_sequence */
    0,                         /* tp_as_mapping */
    0,                         /* tp_hash */
    0,                         /* tp_call */
    0,                         /* tp_str */
    0,                         /* tp_getattro */
    0,                         /* tp_setattro */
    0,                         /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,        /* tp_flags */
    "my.Database object",      /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    Database_methods,          /* tp_methods */
    Database_members,          /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)Database_init,   /* tp_init */
    0,                         /* tp_alloc */
    Database_new,              /* tp_new */
};

#endif // MY_DATABASE
