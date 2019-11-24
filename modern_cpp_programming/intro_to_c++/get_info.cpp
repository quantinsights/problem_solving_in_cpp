// get_info.cpp - This program uses the C++ standard input 
// facility cin to read the terminal input. It is the input
// counterparty to cout.

#include <iostream>

int main()
{
    double temp_C, temp_F;

    std::cout << "\nCentigrade and Fahrenheit converter";
    std::cout << "\nEnter the temperature in degrees celsius = ";
    std::cin >> temp_C;

    temp_F = (9.0 / 5.0) * temp_C + 32;
    std::cout << "\nThe temperature in degrees Fahrenheit =  ";
    std::cout << temp_F;
    return 0;
}