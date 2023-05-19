#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>

class Token
{
    public:

        virtual int type() const;

        virtual void print() const;

        virtual ~Token()
        {

        }
};


#endif // TOKEN_H
