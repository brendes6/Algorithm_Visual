//
//  graphs.hpp
//  Algorithm_Visual
//
//  Created by Brendan Desjardins on 1/2/25.
//

#ifndef graphs_hpp
#define graphs_hpp

#include <iostream>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <string>
#include <thread>
#include <chrono>
#include <stack>
#include <queue>


class Graph {
    
    // Graph object
    // Contains vectors and a hashmap mapping node values (int) to their -
    // corresponding sfml shapes, labels, and neighbors
    // Object methods allow setting/getting/modification of circles and their neighbors

public:
    
    std::vector<int> getNeighbors(int node);
    sf::CircleShape getShape(int node);
    void addNeighbor(int node, int newNeighbor);
    void addCircle(int x, int y);
    int getSize();
    void reset();
    void clear();
    void mark(int node, sf::Color);

    
    std::unordered_map<int, std::vector<int>> neighbors;
    std::vector<sf::CircleShape> shapes;
    int currentNeighborCheck;
    std::vector<sf::VertexArray> lines;
    std::vector<sf::Text> labels;
    int target;
    
};


class graphAlgos {
    
    // graphAlgos class
    // Contains all unchanged sfml objects, such as buttons and text
    // Manages click events and the display, and contains both graph searching algorithms
    // Contains graph object
    
public:
    graphAlgos();
    void run();
    
private:
    bool visit(int node);
    void bfsShortestPath(int origin, int target);
    void dfs(int origin, int target);
    void events();
    void display();
    void handleClicks(sf::Event& event);
    void setState(int state);
    sf::RenderWindow algoWindow;
    sf::RectangleShape clearButton;
    sf::RectangleShape dfsButton;
    sf::RectangleShape bfsButton;
    sf::RectangleShape resetButton;
    sf::RectangleShape targetButton;
    sf::Font algoFont;
    sf::Text clearText;
    sf::Text dfsText;
    sf::Text bfsText;
    sf::Text resetText;
    sf::Text currentState;
    sf::Text targetText;
    sf::Text result;
    int state;
    Graph currentGraph;
};


#endif /* graphs_hpp */
