// function_basics.cpp : This program demonstrates the use of functions
// Function prototypes must be placed just ahead of the first use of the
// function.The build library function sqrt() its prototype in the cmath
// header file.

#include <iostream>

int main()
{
    double x1, x2, y1, y2, d;
    std::cout << "Euclidean distance calculator between two cities";
    std::cout << "Enter the coordintes of the first city";

    std::cout << "\nx1=";
    std::cin >> x1;

    std::cout << "y1=";
    std::cin >> y1;

    std::cout << "x2=";
    std::cin >> x2;

    std::cout << "y2=4";
    std::cin >> y2;

    d = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    std::cout << "Euclidean distance between two cities = " << d;


}