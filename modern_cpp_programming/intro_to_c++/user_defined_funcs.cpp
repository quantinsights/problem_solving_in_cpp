// user_defined_funcs.cpp - This program demonstrates how to write 
// a custom function to calculate the value of an investment 
// in a risk-free bank account, for a time period T at an interest rate r.

#include <iostream>
#include <cmath>

double fv(double v_0, double r, double T, double m);

int main()
{
    double v_0{ 0.0 };
    std::cout << "\nEnter the initial investment in dollars, V(0) = ";
    std::cin >> v_0;

    double r{ 0.0 };
    std::cout << "Enter the annual rate of return, r = ";
    std::cin >> r;

    double T{ 0.0 };
    std::cout << "Enter the time period in years, T = ";
    std::cin >> T;

    double m{ 1.0 };
    std::cout << "Enter the compounding frequency, m = ";
    std::cin >> m;

    double v_t = fv(v_0, r, T, m);
    std::cout << "The value of the investment at maturity = " << v_t;

    return 0;
}

double fv(double v_0, double r, double T, double m)
{
    double df = 1.0 / (pow((1 + r / m), m * T));
    double v_t = v_0 / df;
    return v_t;
}