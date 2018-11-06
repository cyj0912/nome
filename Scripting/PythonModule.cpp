#include "PythonModule.h"

#include <boost/python.hpp>

#include "SceneBuilder.h"

boost::python::object get_builder()
{
    CSceneBuilder* builder = CSceneBuilder::GetSingleton();
    return boost::python::object(builder);
}

BOOST_PYTHON_MODULE(nome)
{
	using namespace boost::python;
	class_<CSceneBuilder>("SceneBuilder", no_init)
		.def("simple_instance", &CSceneBuilder::SimpleInstance);

	def("builder", &get_builder);
}

void RegisterNomePythonModule()
{
	PyImport_AppendInittab("nome", PyInit_nome);
}

void InitPython()
{
	//Init python
	RegisterNomePythonModule();

	Py_Initialize();
}

void FiniPythion()
{
	Py_FinalizeEx();
}

void PythonRun(const char* str)
{
	PyRun_SimpleString(str);
}
