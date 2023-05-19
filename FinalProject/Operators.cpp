#include "Operators.h"
#include <iostream>

Operators::Operators(string ID) : _ID(ID)
{

}

int Operators::type() const
{
    return 2;
}

void Operators::print() const
{
    cout << _ID;
}

int Operators::precedence() const
{
    if (_ID == "+" || _ID == "-")   //lowest prec
    {
        return 1;       //order of op
    }

    else if (_ID == "*" || _ID == "/")      //second level
    {
        return 2;
    }

    else if (_ID == "^")        //power is highest for now
    {
        return 3;
    }

    else                    //anything else should be highest
    {
        return 5;
    }
}

string Operators::op() const
{
    return _ID;
}
