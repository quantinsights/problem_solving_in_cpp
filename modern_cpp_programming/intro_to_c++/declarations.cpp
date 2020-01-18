// declarations.cpp - Before a name(identifier) can be used
// in a C++ program, it must be declared. That is, its type
// must be specified to inform the compiler what kind of entity
// the name refers to.

#include <vector>
#include <string>
#include <complex>

using namespace std;

bool isLeapYear;
char status;
auto count = 1;
const double pi{ 3.1415926535897 };
extern int error_number;

const char* name = "Paul Erdos";
const char* season[] = { "Spring", "Summer", "Autumn", "Winter" };
vector<string> mathematicians = { name,
                                "Mariyam Mirzakhani",
                                "Manjul Bhargava" };
struct Date {
    int dd;
    int mm;
    int yyyy;
};

int day(Date* pDate)
{
    return pDate->dd;
}

template<class T>
T abs(T x)
{
    return x < 0 ? (-x) : x;
}

using Cmplx = std::complex<double>;
enum class Signal {Red, Yellow, Green };