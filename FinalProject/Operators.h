#ifndef OPERATORS_H
#define OPERATORS_H

#include "Token.h"
#include <string>

using namespace std;

class Operators : public Token
{  
    private:

        string _ID;

    public:

        Operators(string ID);       //stored as strings

        virtual int type() const;       //returns an type as int

        virtual void print() const;

        virtual int precedence() const; //precedence determined by order of op

        virtual ~Operators()
        {

        }

        string op() const;      //returns string version
};


#endif // OPERATORS_H
