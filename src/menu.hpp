//
//  menu.hpp
//  Algorithm_Visual
//
//  Created by Brendan Desjardins on 7/11/24.
//

#ifndef menu_hpp
#define menu_hpp

#include <iostream>
#include <SFML/Graphics.hpp>
#include "sorting.hpp"
#include "graphs.hpp"


class gameMenu {
    
    // gameMenu class
    // Class contains all functions for creating and managing the menu window
    // All SFML shapes and texts are stored in this class
  
public:
    gameMenu();
    void run();

private:
    void events();
    void display();
    void handleClicks(sf::Event& event);
    sf::RenderWindow window;
    sf::RectangleShape sortingButton;
    sf::RectangleShape graphsButton;
    sf::Text headerText;
    sf::Text subheaderText;
    sf::Text sortingText;
    sf::Text graphsText;
};

#endif /* menu_hpp */
