# Pyrationals

A simple example of using [pybind11](https://github.com/pybind/pybind11).


This repo consists of 3 main components:
 * The `rational` C++ class which represents immutable Rational Numbers
 * A generator object that genenrates sequences of `rational`s which should converge on Pi (but don't really)
 * A `PYBIND11_MODULE` declaration which makes the  C++ `rational` class and the generator available in Python
