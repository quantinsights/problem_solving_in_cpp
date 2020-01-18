// names.cpp
// A name(identifier) in C++ consists of an arbitrarily long sequence of uppercase and lowercase 
// letters and digits. Underscores are treated as letters. The first character must be a letter. 
// Identifiers are case-sensitive.

// The following exceptions must be noted -

// C++ keywords cannot be used as identifiers in a program.
// The identifiers with a double underscore anywhere are reserved.
// The identifiers that begin with a underscore followed by an uppercase letter 
// are reserved.
// The identifiers that begin with an underscore are reserved in the global namespace.

#include <iostream>

int main()
{
    //Examples of valid names are 
    int hello; 
    char Hello;     //Different from hello
    int flocci_nauci_nihili_pilification_long_identifier_that_is_better_avoided;
    double fo0;
    
    //Examples of character sequences that cannot be used are
    //int  ___;
    //char 012;
    //short 1var;
    //void foo-bar();
    //struct .name{string firstname; string lastname}
    //bool if;

    return 0;
}

