#ifndef GRAPH_H
#define GRAPH_H

#include "Graph_Info.h"
#include <SFML/Graphics.hpp>

//#include <vector>
#include "MyVector.h"

using namespace std;

class Graph
{
    private:

        Graph_info* _info;  //every class uses graph info

        MyVector <sf::Vector2f> _points;  //_points is an entire set of points
                                        //that are used to graph an image

    public:

        Graph(Graph_info* graph_info);  //constructor using graph info

        void Set_Info(Graph_info* graph_info);  //changes info

        void Update(Graph_info graph_info); //uses plot object

        void Draw(sf::RenderWindow& window);    //draws empty graph


        void draw_background(sf::RenderWindow& window); //draws window
                                                        //dimensions aka graph
        void draw_axes(sf::RenderWindow& window);       //axis y and x

        void draw_curve(sf::RenderWindow& window);      //dots
};

#endif
