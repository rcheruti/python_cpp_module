
#ifdef MY_PESSOA
#else
#define MY_PESSOA

#include <Python.h>
#include <structmember.h>

typedef struct {
    PyObject_HEAD
    int idade;
    char* nome;
} Pessoa ;

static PyMemberDef Pessoa_members[] = {
    {"idade", T_INT, offsetof(Pessoa, idade), 0, "my.Pessoa idade"},
    {NULL}  /* Sentinel */
};

static PyObject* Pessoa_nome_getter(Pessoa* self) {
    return Py_BuildValue("s", self->nome );
}
static int Pessoa_nome_setter(Pessoa* self, PyObject* args) {
    if( !PyArg_Parse(args, "s", &self->nome ) ) return -1;
    return 0;
}

static PyGetSetDef Pessoa_getSet[] = {
    {"nome", (getter)Pessoa_nome_getter, (setter)Pessoa_nome_setter, "my.Pessoa nome", NULL},
    {NULL}  /* Sentinel */
};

// --------------------------------------
// Python integration

static void Pessoa_dealloc(PyObject* self) {
    Py_TYPE(self)->tp_free(self);
}
static PyObject* Pessoa_new(PyTypeObject *type, PyObject *args, PyObject *kwds) {
    return (PyObject*) type->tp_alloc(type, 0);
}
static int Pessoa_init(Pessoa* self, PyObject* args, PyObject* kwds) {
    static const char *Pessoa_kwList[] = {"nome", "idade", NULL};
    if( args == NULL ) args = PyTuple_New(0);

    if( !PyArg_ParseTupleAndKeywords(args, kwds, "si", const_cast<char**>(Pessoa_kwList), 
        &self->nome, &self->idade ) ) return -1;
    
// printf("--self->nome: %s, idade: %d / offset: %d \n", self->nome, self->idade, offsetof(Pessoa, idade) );
    return 0;
}



static PyMethodDef Pessoa_methods[] = {
    {NULL}  /* Sentinel */
};
static PyTypeObject PessoaType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "my.Pessoa",               /* tp_name */
    sizeof(Pessoa),            /* tp_basicsize */
    0,                         /* tp_itemsize */
    Pessoa_dealloc,            /* tp_dealloc */
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
    "my.Pessoa object",        /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    Pessoa_methods,            /* tp_methods */
    Pessoa_members,            /* tp_members */
    Pessoa_getSet,             /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)Pessoa_init,     /* tp_init */
    0,                         /* tp_alloc */
    Pessoa_new,                /* tp_new */
};

#endif // MY_PESSOA