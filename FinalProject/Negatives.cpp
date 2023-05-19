#include "Negatives.h"
#include <iostream>

using namespace std;

Negatives::Negatives() : Operators("-")
{

}

int Negatives::type() const
{
    return 2;
}

void Negatives::print() const
{
    cout << '-';
}

int Negatives::prec() const
{
    return 4;
}
