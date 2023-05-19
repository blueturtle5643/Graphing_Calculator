#include "Numbers.h"
#include <iostream>

using namespace std;

Numbers::Numbers(float num) : _value(num)
{

}

int Numbers::type() const
{
    return 1;
}

void Numbers::print() const
{
    cout << _value;
}

int Numbers::get() const
{
    return _value;
}
