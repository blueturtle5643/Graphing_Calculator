#ifndef PLOT_H
#define PLOT_H

#include "Graph_Info.h"
#include "Graph.h"
#include "Queue.h"
#include "Token.h"

//#include <vector>
#include "MyVector.h"
#include "AddEntry.h"

using namespace std;

class Plot  //Plot handles SY : RPN : Coordinate Translation
{
    private:

        Queue <Token*> _post_fix;  //postfix queue for SY

        Graph_info* _info;  //info for manipulating graph design

    public:

        Plot(Graph_info* graph_info);   //constructor

        ~Plot();

        void Set_Info(Graph_info* graph_info);  //changes info

        MyVector <sf::Vector2f> operator()();  //takes an entire set of points
                                            //and plots points

        Queue <Token*> tokenize(const string& equation) const;
};

#endif
