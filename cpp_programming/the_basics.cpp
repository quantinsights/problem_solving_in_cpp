// A history of C++.

// C++ was invented by Bjarne Stroustrup. He designed and implemented the language because 
// he wanted to distribute the services of a UNIX kernel across multiprocessors and local-area
// networks. For that, he needed some event-driven simulations, for which Simula would be ideal, except
// performance considerations. He also needed to deal directly with hardware and provide 
// high-performance concurrent programming mechanisms for which C was ideal, except its 
// weak support for modularity. The result of adding Simula-style classes to C, "C with Classes",
// was used for major projects. The first use of C++ outside a research organisation started in 
// July 1983.

// Compiling a C++ Program.

// C++ is a compiled language. For a program to run, the source code has to be processed by a compiler,
// producing object files, which are combined a linker yielding an executable program.
// A C++ program typically consists of many source code files (usually simply called source files). 

// The ISO  C++ standard defines two kinds of entitites:

// Core language features, such as built-in types (e.g. char and int) and loops(e.g. for statement
// and while-statements).

// Standard-library components, such as containers (e.g. vector and map) and I/O operations (e.g. <<).

// Hello World.

// The only way to learn a new programming language is by writing programs in it. The first program
// to write is the same in all languages: print the words, Hello World.

#include<iostream>

int main()
{
    std::cout << "Hello World\n";
    return 0;
}