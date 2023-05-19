#include "Functions.h"
#include <iostream>

Functions::Functions(string ID) : Operators(ID)
{

}

int Functions::type() const
{
    return 5;
}

void Functions::print() const
{
    Operators::print();
}

int Functions::prec() const
{
    return 5;       //highest prec
}
