#ifndef GRAPH_INFO_H
#define GRAPH_INFO_H

#include <string>
#include <SFML/Graphics.hpp>

using namespace std;

struct Graph_info
{
    string _equation;   //will be used as the expression to be evaluated and
                        //graphed
    sf::Vector2f _window_dimensions;

    sf::Vector2f _origin;   //pointer of cursor or selected point that graph
                            //will be drawn around
    // sf::Vector2f _scale;

    sf::Vector2f _domain;   //the x values to be sent in the Plot class

    int _points;    //the amount of points to be incremented appropriately
};                  //in determining the Plot class

#endif
