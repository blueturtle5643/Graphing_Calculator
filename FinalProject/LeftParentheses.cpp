#include "LeftParentheses.h"
#include <iostream>

using namespace std;

int LeftParentheses::type() const
{
    return 3;       //unique int
}

void LeftParentheses::print() const
{
    cout << '(';
}
