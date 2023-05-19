#ifndef VARIABLES_H
#define VARIABLES_H

#include <string>
#include "Numbers.h"

using namespace std;

class Variables : public Numbers
{

    private:

        string _name;

    public:

        Variables(string name);     //just stores x and stuff, same as numbers

        virtual int type() const;

        virtual void print() const;
};

#endif // VARIABLES_H
