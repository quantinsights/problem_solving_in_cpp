// structure_of_declarations.cpp 
// Bjarne Stroustrup in his book writes that we can consider a declaration
// as having five parts (in order):

// Optional prefix specifiers (e.g. static or virtual)
// A base data-type (E.g. vector<double> or const int)
// Declarator composed of a name and optionally a declarator operator
//                              (E.g. n, count, sqrt , p[7], *phone_numbers[])
// Optional suffix specifiers (E.g. const or noexcept)
// Optional initializer or function body (E.g. {8,6,2} or {return x;})

int main()
{
    const char* planets[] {
        "Mercury",  "Venus",    "Earth",
        "Mars",     "Jupiter",  "Saturn",
        "Uranus",   "Neptune"
    };

    // planets is an array of character pointers. 
    // Here, the base datatype is const char, the name of the entity is planets
    // so the declarator is * planets[] and the initializer is the = followed
    // by the curly brace initializer list {}.

    // A specifier is any non-type attribute of what is being declared such as
    // virtual or constexpr.

    // A declarator is composed of a name and optionally some declarator operators.
    // I have reproduced this table of the most common declarator operators from
    // Stroustrup's book.

    /*

    +------------------------------------------------+
    |              Declarator operators              |
    +-----------+-----------+------------------------+
    | prefix    | *         | pointer to             |
    | prefix    | *const    | constant pointer to    |
    | prefix    | &         | lvalue reference to    |
    | prefix    | &&        | rvalue reference to    |
    | postfix   | []        | array of               |
    | postfix   | ()        | function               |
    +-----------+-----------+------------------------+

    */

    // To understand C++ declarations, follow these rules.
    // (https://en.cppreference.com/w/cpp/language/declarations)

    // Precedence from high-to-low:
    // 1. Parentheses grouping together a part of the declaration.
    // 2. Postfix operators such as () (indicating a function) and [] (indicating an array).
    // 3. Prefix operators such as * (pointer to) and & (lvalue reference to).

    // If a cv-qualifier (const or volatile) occurs to the right of an asterisk *, 
    // (e.g. int * const ptr) then the cv-qualifier applies to the pointer, so this is a 
    // ptr is a constant pointer to an integer. Otherwise, if a cv-qualifier occurs to the 
    // left of an asterisk and next to a data-type, then the cv-qualifier applies to the type.
    // E.g. the declaration const int * ptr;  says ptr is pointer to a constant integer.

    // To understand a declaration such as 

    // int const * const * (*p[])(float); 

    // we do the following:

    // 1. Begin at the declaration's name (e.g. p) and say p is a ... Follow the above precedence
    // rules and going outwards from the name, apply the following.
    
    // 2. If to the immediate right, there are brackets [], say "an array of..."

    // 3. If to the immediate right, there is an open parentheses (param-list) e.g. (), (float, int)
    // then say, "a function with parameters returning ..."

    // 4. If to the immediate left there is an asterisk and possibly cv-qualifiers, that say
    // "pointer(s) to ....".

    // 5. Repeat 2-5 as necessary.

    // So, in our example, int const * const * (*p[])(float ), p is an array of pointers to functions
    // that accept one float argument and return a pointer to int const * const, that is constant pointer
    // to an integer constant. Thus, p is an array of pointers to functions that have the prototype

    // const int * const * funcname (float);

    return 0;
}