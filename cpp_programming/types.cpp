// Fundamental types.

// C++ has a set of fundamental types corresponding to the most common basic storage units
// of the computer and the most common ways of using them to hold data:

// A Boolean type(bool)
// Character types(char)
// Integer types (short, int, long and long long)
// Floating-point types (such as float and double)
// A type void, used to signify absence of information.

// From these types, we can construct other types using declarator operators:
// Pointer types (such as int*)
// Array types (char[]_
// Reference types (such as double& and vector<int>&&)

// Also, a user can define dditional types:
// Data structures and classes.
// Enumeration types.

// The boolean, character and integer types are collectively called integral types. The integral and 
// floating-point types are collectively called arithmetic types. Enumerations and clsses are called 
// user-defined types because they must be specified by users rather thn being availble for
// use without previous declaration, the way fundamental types. In contrast, fundamental types
// pointers and references are collective referred as built-in types. 

// A boolean, bool can have one of the two values true or false. A Boolean variable
// is usd to express the results of a logical expression. For example,

bool isGreater(int a, int b) { return a > b; }

int main()
{
    bool isEven = (10 % 2) == 0;

    // By definition, true has the value 1 when converted to and integer and false has the value 0.
    // Conversely, integers can be implicitly converted to book values, non-zero integers convert to true
    // and 0 converts to false.

    // Character types.

    // There are many character sets and character encodings in use. C++ provides a 
    // variety of character types that reflect that -

    // char: The default character types, used for program text.
    // A char is used for the implementation's character set and is usually 8  bits.

    // signed char: Like char, but guaranteed to be signed, that is capable of holding both
    // positive and negative values.

    // unsigned char: Like char, but guaranteed to be unsigned.

    // wchar_t :
    return 0;
}