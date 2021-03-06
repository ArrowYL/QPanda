#include "pybind11/pybind11.h"
#include "pybind11/stl.h"
#include "QPandaAPI/QPandaAPI.h"
#include <map>
#include <iostream>
using std::map;
using std::string;
namespace py = pybind11;
using namespace QPanda;

PYBIND11_MODULE(pyQPanda, m)
{
    m.doc() = "document";
#if 1
    py::class_<QPandaSDK>(m, "QPandaSDK")
        .def(py::init<>())
        .def("getIntance",&(QPandaSDK::getIntance),"getIntance")
        .def("loadFile", &(QPandaSDK::loadFile))
        .def("setComputeUnit", &(QPandaSDK::setComputeUnit))
        .def("run", &(QPandaSDK::run))
        .def("getResult", &(QPandaSDK::getResult))
        .def("getQuantumState", &(QPandaSDK::getQuantumState))
        ;
#endif
}