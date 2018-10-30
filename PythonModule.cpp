#include "PythonModule.h"

#include <boost/python.hpp>

const char* greet()
{
	return "hello from c++";
}

BOOST_PYTHON_MODULE(nome)
{
	using namespace boost::python;
	def("greet", greet);
}

void RegisterNomePythonModule()
{
	PyImport_AppendInittab("nome", PyInit_nome);
}

void InitPython()
{
	//Init python
	Py_SetPath(L"E:/Dev/vcpkg/packages/python3_x64-windows/share/python3/Lib");
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
