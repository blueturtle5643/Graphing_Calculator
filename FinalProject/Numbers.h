#ifndef NUMBERS_H
#define NUMBERS_H

#include "Token.h"

class Numbers : public Token
{        
    private:

        float _value;

    public:

        Numbers(float num);   //negative unary operator in progress

        virtual int type() const;

        virtual void print() const;

        int get() const;
};

#endif // NUMBERS_H

