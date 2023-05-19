#include "Graph.h"
#include "Plot.h"

Graph::Graph(Graph_info *graph_info) : _info(graph_info)
{

}

void Graph::Set_Info(Graph_info *graph_info)
{
    if(_info)
    {
        delete _info;
    }

    _info = graph_info;
}

void Graph::Update(Graph_info graph_info)
{
    Plot plotter(_info);

    _points = plotter();
}

void Graph::Draw(sf::RenderWindow& window)
{
    draw_background(window);        //too much code in graph, made a draw
                                    //to clean stuff up
    draw_axes(window);

    draw_curve(window);
}

void Graph::draw_background(sf::RenderWindow& window)
{
    //set background

    sf::RectangleShape background;

    background.setSize(sf::Vector2f(_info->_window_dimensions.x,
                                    _info->_window_dimensions.y));

    //window dimensions will essentially be the graph space so the background
    //aka the graph size will be based off of it

    //background.setFillColor(sf::Color(255, 229, 180)); // peach color

    //background.setFillColor(sf::Color(255, 216, 209));

    //background.setFillColor(sf::Color(153, 153, 255));

    background.setFillColor(sf::Color(176, 76, 76));

    //MAY CHANGE

    window.draw(background);

    //background grid ??
}

void Graph::draw_axes(sf::RenderWindow& window)
{
    //calculate pixel offsets corresponding to
    //translation of 1 unit up/down/left/right

    float domainchange = _info->_domain.y - _info->_domain.x;

    //same concept of finding length of domain

    float xincrease =  _info->_window_dimensions.x / domainchange;

    float yincrease = _info->_window_dimensions.y / domainchange;

    //acounting for increments based off of window dimensions(graph)

    int axis_thickness = 2;

    //since example projects went with even values for screen size etc.
    //I went with same design and decided for 2 for axis thickness

    //MAY CHANGE

    sf::RectangleShape axis_x, axis_y;

    //sf::Color axis_color(120,57,55);

    //sf::Color axis_color(199, 227, 220);

    //sf::Color axis_color(204, 255, 204);

    //sf::Color axis_color(235, 231, 231);

    sf::Color axis_color(240, 197, 154);

    axis_x.setSize(sf::Vector2f(_info->_window_dimensions.x, axis_thickness));

    axis_x.setPosition(0, (_info->_window_dimensions.y / 2) -
                       (axis_thickness/ 2) + (_info->_origin.y * yincrease));

    axis_x.setFillColor(axis_color);

    //axis_x.setFillColor(sf::Color(240, 197, 154));

    //axis_x.setFillColor(sf::Color(240, 197, 154));

    window.draw(axis_x);

    axis_y.setSize(sf::Vector2f(axis_thickness, _info->_window_dimensions.y));

    axis_y.setPosition((_info->_window_dimensions.x / 2) - (axis_thickness / 2)
                     + (-1 * _info->_origin.x * xincrease), 0);

    axis_y.setFillColor(axis_color);

    //axis_y.setFillColor(sf::Color(235, 231, 231));

    window.draw(axis_y);

    // axis tick marks??
}

void Graph::draw_curve(sf::RenderWindow& window)
{
    sf::CircleShape dot;

    const float DOT_RADIUS = 1;

    dot.setRadius(DOT_RADIUS);

    //dot.setFillColor(sf::Color(166, 76, 255));

    //dot.setFillColor(sf::Color(255, 255, 153));

    dot.setFillColor(sf::Color(235, 231, 231));

    dot.setOrigin(DOT_RADIUS, DOT_RADIUS); // set to middle of dot

    for(int i = 0; i < _points.returnsize(); i++)
    {
        dot.setPosition(_points[i]);        //since dot logic removes need
                                            //for realigning, can run through
        window.draw(dot);                   //vector
    }
}
