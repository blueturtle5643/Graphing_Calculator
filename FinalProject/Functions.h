#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "Operators.h"
#include <string>

class Functions : public Operators
{
    public:

        Functions(string ID);       //passed as strings for now

        virtual int type() const;

        virtual void print() const;

        virtual int prec() const;   //derives from operator, highest prec
};

#endif // FUNCTIONS_H
