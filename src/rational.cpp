#include "rational.h"

std::ostream &operator<<(std::ostream &os, rational const &r) 
{ 
    return os << r.numerator << "/" << r.denominator;
}

int rational::find_gcd(int a, int b)
{
    if(a == b) return a;
    if(a > b) {
        int tmp = a;
        a = b;
        b = tmp;
    }

    int remainder = b % a;
    if (remainder == 0) return a;
    return find_gcd(remainder, a);
}