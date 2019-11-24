// declarations_and_assignments.cpp - This program illustrates the difference
// between a declaration and an assignment statement in C++.

#include <iostream>

int main()
{
    int hours;                  //declare an integer variable

    hours = 24;                 //assign a value to the variable

    std::cout << "I have";      //display the value of the variable
    std::cout << hours;
    std::cout << " to reach the finish line";
    std::cout << std::endl;

    hours = hours - 1;          //modify the variable
    std::cout << "Tick, tock. Now I have " << hours
        << " hours to make it to the finish!" << std::endl;
}