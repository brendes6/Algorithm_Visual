//
//  sorting.hpp
//  Algorithm_Visual
//
//  Created by Brendan Desjardins on 7/30/24.
//

#ifndef sorting_hpp
#define sorting_hpp

#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <thread>
#include <chrono>

class listValue{
    
    // listValue object
    // Object containing integers value and index, as well as a shape that corresponds to the value and index
    // Object methods are used to modify listValue's shape, value, or index
    // Modifications are constantly made in the process of sorting rectList
public:
    void setShape(int listSize);
    void setValue(int val);
    void setIndex(int ind);
    sf::RectangleShape getShape();
    sf::RectangleShape shape;
    int value;
    int index;
    
};

class sortingAlgos{
    
    // sortingAlgos class
    // Contains all SFML shapes/text as well as all member functions and data neccesary -
    // for the function of the program overall
    // All sorting algorithms are contained in this class
    // Functions for creating and maintaining the program function are contained in this class
    // All unchanged SFML objects are contained in this class
    // Data and lists neccesary for algorithm implementation are contained in this class
    
public:
    sortingAlgos();
    void run();
    
private:
    void selectionSort();
    void bubbleSort();
    void insertionSort();
    void mergeSort(int l, int r);
    void merge(int l, int r, int m);
    void events();
    void display();
    void handleClicks(sf::Event& event);
    void generate_list(int size);
    int listSize;
    std::vector<int> list;
    std::vector<listValue> rectList;
    sf::RenderWindow algoWindow;
    sf::RectangleShape selectionButton;
    sf::RectangleShape resetButton;
    sf::RectangleShape bubbleButton;
    sf::RectangleShape insertionButton;
    sf::RectangleShape mergeButton;
    sf::RectangleShape resetButton2;
    sf::Text resetText;
    sf::Text selectionText;
    sf::Text bubbleText;
    sf::Text insertionText;
    sf::Text mergeText;
    sf::Text resetText2;
    
};


#endif /* sorting_hpp */
