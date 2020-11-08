import pytest

from pyrational import Rational


def test_constructors():
    r = Rational(1, 2)
    assert r.numerator == 1
    assert r.denominator == 2

    i = Rational(3)
    assert i.numerator == 3
    assert i.denominator == 1


def test_fields_are_readonly():
    r = Rational(1, 2)
    with pytest.raises(AttributeError):
        r.numerator = 3
    with pytest.raises(AttributeError):
        r.denominator = 4


def test_repr():
    assert str(Rational(1, 2)) == "1/2"


def test_equality():
    assert Rational(1, 2) == Rational(1, 2)
    assert 2 == Rational(2)
    assert Rational(2) == 2


def test_multiplication():
    assert Rational(1, 2) * Rational(1, 2) == Rational(1, 4)
    assert Rational(1, 3) * 2 == Rational(2, 3)
    assert 2 * Rational(1, 3) == Rational(2, 3)


def test_addition():
    assert Rational(1, 3) + Rational(1, 3) == Rational(2, 3)
    assert Rational(1, 2) + 1 == Rational(3, 2)
    assert 1 + Rational(1, 2) == Rational(3, 2)


def test_float_cast():
    assert float(Rational(1,2)) == pytest.approx(0.5)