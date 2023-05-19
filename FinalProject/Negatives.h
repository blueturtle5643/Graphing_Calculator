#ifndef NEGATIVES_H
#define NEGATIVES_H

#include "Operators.h"

class Negatives : public Operators
{
    public:

        Negatives();

        virtual int type() const;

        virtual void print() const;

        virtual int prec() const;
};

#endif // NEGATIVES_H
