#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>


class rational 
{
public:
    
    const int numerator;
    const int denominator;

    rational(const int i) : numerator(i), denominator(1) {}

    rational(const int numerator_, const int denominator_) : 
        rational(numerator_, denominator_, find_gcd(numerator_, denominator_)) {}

    rational(const rational & other) : numerator(other.numerator), denominator(other.denominator){}

    rational(rational && other) : numerator(other.numerator), denominator(other.denominator){}

    bool operator==(const rational & other) const 
    {
        return numerator == other.numerator && denominator == other.denominator;
    }

    bool operator==(const int i) const 
    {
        return denominator == 1 && numerator == i;
    }

    rational operator*(const int x) const 
    {
        return rational(numerator * x, denominator);
    }

    rational operator*(const rational &other) const 
    {
        return rational(numerator * other.numerator, denominator * other.denominator);
    }

    rational operator+(const int x) const
    {
        return rational(numerator + x * denominator, denominator);
    }

    rational operator+(const rational &other) const 
    {
        return rational(numerator * other.denominator + denominator * other.numerator, 
            denominator * other.denominator);
    }
    
    rational operator-(const rational &other) const
    {
        return rational(numerator * other.denominator - denominator * other.numerator, 
            denominator * other.denominator);
    }

    operator std::string() const
    {
        std::ostringstream os;
        os << *this;
        return os.str();
    }
    
    operator float() const
    {
        if(numerator == 0) return  0.0; 
        return static_cast<float>(numerator) / static_cast<float>(denominator);
    }

    friend std::ostream &operator<<(std::ostream &os, rational const &r);

private:
    
    rational(const int numerator_, const int denominator_, const int gcd): 
        numerator(signum(denominator_) * numerator_ / gcd), 
        denominator(abs(denominator_) / gcd) {}

    static int find_gcd(int a, int b);
    
    static int signum(int x) { return x >= 0 ? 1 : -1; }
};