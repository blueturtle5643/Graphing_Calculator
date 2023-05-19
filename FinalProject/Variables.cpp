#include "Variables.h"
#include <iostream>

Variables::Variables(string name) : Numbers(0), _name(name)
{

}

int Variables::type() const
{
    return 6;
}

void Variables::print() const
{
    cout << _name;
}
