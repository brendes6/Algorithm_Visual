//
//  menu.cpp
//  Algorithm_Visual
//
//  Created by Brendan Desjardins on 7/11/24.
//

#include "menu.hpp"

gameMenu::gameMenu()
: window(sf::VideoMode(640, 480), "Main Menu")
{
    // gameMenu()
    // Initializer function creates and initializes window and all sfml objects used in the menu
    
    sortingButton.setSize(sf::Vector2f(190.f, 95.f));
    sortingButton.setPosition(70, 300);
    sortingButton.setFillColor(sf::Color(200, 200, 200));
    sortingButton.setOutlineColor(sf::Color::Black);
    sortingButton.setOutlineThickness(2.f);
    graphsButton.setSize(sf::Vector2f(190.f, 95.f));
    graphsButton.setPosition(370, 300);
    graphsButton.setFillColor(sf::Color(200, 200, 200));
    graphsButton.setOutlineColor(sf::Color::Black);
    graphsButton.setOutlineThickness(2.f);

}

void gameMenu::run() {
    // void run()
    // Initializes menu font and all text used in the menu
    // Game loop runs events() and display() as long as the window is open
    
    sf::Font menuFont;
    if (!menuFont.loadFromFile("/System/Library/Fonts/SFNS.ttf")){
        std::cerr << "Font not found\n";
        return;
    }
    headerText.setFont(menuFont);
    headerText.setString("Welcome to Algorithm Visualizer!");
    headerText.setCharacterSize(40);
    headerText.setFillColor(sf::Color::Black);
    headerText.setPosition(50.f, 50.f);
    subheaderText.setFont(menuFont);
    subheaderText.setString("Made by Brendan Desjardins");
    subheaderText.setCharacterSize(20);
    subheaderText.setFillColor(sf::Color::Black);
    subheaderText.setPosition(50.f, 150.f);
    sortingText.setFont(menuFont);
    sortingText.setString("Sorting Algorithms");
    sortingText.setCharacterSize(20);
    sortingText.setFillColor(sf::Color::Black);
    sortingText.setPosition(75.f, 340.f);
    graphsText.setFont(menuFont);
    graphsText.setString("Graph Algorithms- \n Coming Soon");
    graphsText.setCharacterSize(20);
    graphsText.setFillColor(sf::Color::Black);
    graphsText.setPosition(385.f, 330.f);

    
    
    while (window.isOpen()){
        events();
        display();
    }
}

void gameMenu::handleClicks(sf::Event& event){
    // void handleClicks()
    // All mouseclick events are passed into this function
    // Due to menu simplicity, only checks for user clicking the sorting algorithms button
    // Runs sorting algorithms window is button is clicked
    
    if (300 < event.mouseButton.y && 395 > event.mouseButton.y){
        if (70 < event.mouseButton.x && event.mouseButton.x < 260){
            sortingAlgos newSort;
            window.close();
            newSort.run();
        }
        else if (370 < event.mouseButton.x && event.mouseButton.x < 560){
            graphAlgos newGraph;
            window.close();
            newGraph.run();
        }
    }
}

void gameMenu::events() {
    // void events() function
    // Polls events from the window
    // Due to simplicity of menu page, only checks for mouse clicks and window closing
    
    sf::Event event;
    while (window.pollEvent(event)){
        if (event.type == sf::Event::MouseButtonPressed){
            handleClicks(event);
            break;
        }
        if (event.type == sf::Event::Closed){
            window.close();
            break;
        }
    }
}


void gameMenu::display() {
    // void display() function
    // Displays all buttons and texts visible on screen
    
    window.clear(sf::Color::White);
    window.draw(sortingButton);
    window.draw(graphsButton);
    window.draw(headerText);
    window.draw(subheaderText);
    window.draw(sortingText);
    window.draw(graphsText);
    window.display();
}
