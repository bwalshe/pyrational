#include <pybind11/pybind11.h>

#include "rational.h"
#include "generators.h"

namespace py = pybind11;

PYBIND11_MODULE(pyrational, m) {
    m.doc() = R"pbdoc(
        Pybind11 rational number example plugin
        -----------------------

        .. currentmodule:: pyrational

        .. autosummary::
           :toctree: _generate

           add
           subtract
    )pbdoc";

    py::class_<rational>(m, "Rational")
        .def(py::init<int, int>())
        .def(py::init<int>())
        .def_readonly("numerator", &rational::numerator)
        .def_readonly("denominator", &rational::denominator)
        .def("__repr__", [](const rational &r){return static_cast<std::string>(r);})
        .def("__eq__", py::overload_cast<const rational &>(&rational::operator==, py::const_))
        .def("__eq__", py::overload_cast<const int>(&rational::operator==, py::const_))
        .def("__req__", py::overload_cast<const int>(&rational::operator==, py::const_))
        .def("__mul__",  py::overload_cast<const rational &>(&rational::operator*, py::const_))
        .def("__mul__",  py::overload_cast<const int>(&rational::operator*, py::const_))
        .def("__rmul__", py::overload_cast<const int>(&rational::operator*, py::const_))
        .def("__add__",  py::overload_cast<const rational &>(&rational::operator+, py::const_))
        .def("__add__",  py::overload_cast<const int>(&rational::operator+, py::const_))
        .def("__radd__", py::overload_cast<const int>(&rational::operator+, py::const_))
        .def("__float__", [](const rational &r){return static_cast<float>(r);});

    py::class_<estimate_pi>(m, "estimate_pi")
        .def(py::init<float>())
        .def("__iter__", [](estimate_pi &e){return e;})
        .def("__next__", [](estimate_pi &e){
            if(e.finished()) throw py::stop_iteration(); 
            return e.next();
        });

   
#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}
