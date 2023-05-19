#include "Coordinate_Translator.h"

Coordinate_Translator::Coordinate_Translator(Graph_info* graph_info) 
    : _info(graph_info)
{

}

sf::Vector2f Coordinate_Translator::translate(sf::Vector2f point)
{
    float domainchange = _info->_domain.y - _info->_domain.x;

    //domain change

    float xincrease = _info->_window_dimensions.x / domainchange;

    float yincrease = _info->_window_dimensions.y / domainchange;

    //find the offsets for both y and x

    float screenx = (_info->_window_dimensions.x / 2) -
             (_info->_origin.x * xincrease) + (point.x * xincrease);

    //screen coord requires several factors
    //division of the window dimensions to simulate a graph (origin in middle
    //of the screen), an increase extracted from domain change and the graph
    //width and length

    //screen coords can then be found by adding the origin incremented x
    //with the graph coord x of the line also incremented properly, and finally
    //subtracting it from the origin of the graph

    float screeny = (_info->_window_dimensions.y / 2) +
        (_info->_origin.y * yincrease) - (point.y * yincrease);

    //y operates on same principle

    return sf::Vector2f(screenx, screeny);

    //returns an vector(x,y) with scren coords
}

sf::Vector2f Coordinate_Translator::operator() (sf::Vector2f point)
{
    return translate(point);
}
