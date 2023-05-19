#ifndef SYSTEM_H
#define SYSTEM_H

#include <SFML/Graphics.hpp>
#include "Graph_Info.h"
#include "Graph.h"
//#include <vector>

using namespace std;

class System
{
    private:

        Graph _g;

    public:

        System(Graph_info* graph_info);

        void Set_Info(Graph_info* graph_info);

        void Step(int command, Graph_info* graph_info);

        //void Step(int command, Graph_info* graph_info, sf::RenderWindow& window);

        void Draw(sf::RenderWindow& window);

};

#endif // SYSTEM_H
