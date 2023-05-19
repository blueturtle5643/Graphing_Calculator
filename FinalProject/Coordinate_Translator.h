#ifndef COORDINATE_TRANSLATOR_H
#define COORDINATE_TRANSLATOR_H

#include <SFML/Graphics.hpp>
#include "Graph_Info.h"

class Coordinate_Translator
{
    private:

        Graph_info* _info;  //graph info object passed in every class

    public:

        Coordinate_Translator(Graph_info* graph_info);  //constructor using graph info

        sf::Vector2f translate(sf::Vector2f point);

        //translate converts a coordinate pair (x,y) into screen coords

        sf::Vector2f operator() (sf::Vector2f point);

        //calls translate
};


#endif
