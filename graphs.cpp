//
//  graphs.cpp
//  Algorithm_Visual
//
//  Created by Brendan Desjardins on 1/2/25.
//

#include "graphs.hpp"


// All Graph object methods, including getters, setters, and
// methods that can clear/reset the graph

std::vector<int> Graph::getNeighbors(int node){
    return neighbors[node];
}
void Graph::addNeighbor(int node, int newNeighbor){
    neighbors[node].push_back(newNeighbor);
}
sf::CircleShape Graph::getShape(int node){
    return shapes[node];
}
void Graph::addCircle(int x, int y){
    sf::CircleShape newCircle;
    newCircle.setPosition(x-25, y-25);
    newCircle.setRadius(25);
    newCircle.setFillColor(sf::Color::Black);
    shapes.push_back(newCircle);
}
int Graph::getSize(){
    return shapes.size();
}
void Graph::clear(){
    shapes.clear();
    neighbors.clear();
    lines.clear();
}
void Graph::mark(int node, sf::Color color){
    // Mark a node based on the specified color
    shapes[node].setFillColor(color);
}
void Graph::reset(){
    // Reset all shape colors and the target node
    for (int i=0; i<shapes.size(); i++){
        shapes[i].setFillColor(sf::Color::Black);
    }
    target = -1;
}


graphAlgos::graphAlgos()
:algoWindow(sf::VideoMode(840, 620), "Graph Algorithms"){
    // Initialize all buttons as SFML RectangleShapes, and intitialize graph attributes
    clearButton.setSize(sf::Vector2f(150.f, 40.f));
    clearButton.setPosition(650, 50);
    clearButton.setFillColor(sf::Color(200, 200, 200));
    clearButton.setOutlineColor(sf::Color::Black);
    clearButton.setOutlineThickness(2.f);
    dfsButton.setSize(sf::Vector2f(150.f, 40.f));
    dfsButton.setPosition(650, 120);
    dfsButton.setFillColor(sf::Color(200, 200, 200));
    dfsButton.setOutlineColor(sf::Color::Black);
    dfsButton.setOutlineThickness(2.f);
    resetButton.setSize(sf::Vector2f(150.f, 40.f));
    resetButton.setPosition(650, 260);
    resetButton.setFillColor(sf::Color(200, 200, 200));
    resetButton.setOutlineColor(sf::Color::Black);
    resetButton.setOutlineThickness(2.f);
    bfsButton.setSize(sf::Vector2f(150.f, 40.f));
    bfsButton.setPosition(650, 190);
    bfsButton.setFillColor(sf::Color(200, 200, 200));
    bfsButton.setOutlineColor(sf::Color::Black);
    bfsButton.setOutlineThickness(2.f);
    targetButton.setSize(sf::Vector2f(150.f, 40.f));
    targetButton.setPosition(650, 330);
    targetButton.setFillColor(sf::Color(200, 200, 200));
    targetButton.setOutlineColor(sf::Color::Black);
    targetButton.setOutlineThickness(2.f);
    currentGraph.currentNeighborCheck = -1;
    currentGraph.target = -1;
    state = 0;
    
}

void graphAlgos::run(){
    // Loads font and initializes all text displayed on the screen
    if (!algoFont.loadFromFile("/System/Library/Fonts/SFNS.ttf")){
        std::cerr << "Font not found\n";
        return;
    }
    clearText.setFont(algoFont);
    clearText.setString("Clear Graph");
    clearText.setCharacterSize(20);
    clearText.setFillColor(sf::Color::Black);
    clearText.setPosition(665.f, 55.f);
    dfsText.setFont(algoFont);
    dfsText.setString("Depth-First Search");
    dfsText.setCharacterSize(17);
    dfsText.setFillColor(sf::Color::Black);
    dfsText.setPosition(660.f, 125.f);
    resetText.setFont(algoFont);
    resetText.setString("Reset Search");
    resetText.setCharacterSize(20);
    resetText.setFillColor(sf::Color::Black);
    resetText.setPosition(665.f, 265.f);
    bfsText.setFont(algoFont);
    bfsText.setString("Breadth-First Search");
    bfsText.setCharacterSize(16);
    bfsText.setFillColor(sf::Color::Black);
    bfsText.setPosition(658.f, 197.f);
    currentState.setPosition(620.f, 380.f);
    currentState.setFillColor(sf::Color::Black);
    currentState.setCharacterSize(15);
    currentState.setFont(algoFont);
    targetText.setPosition(657.f, 337.f);
    targetText.setFillColor(sf::Color::Black);
    targetText.setCharacterSize(16);
    targetText.setString("Choose Target Node");
    targetText.setFont(algoFont);
    result.setPosition(657.f, 437.f);
    result.setFillColor(sf::Color::Black);
    result.setCharacterSize(16);
    result.setString("");
    result.setFont(algoFont);
    
    // Game loop polls events and updates display while window is open
    while (algoWindow.isOpen()){
        events();
        display();
    }
}

void graphAlgos::setState(int state){
    
    // Updates the message of currentState string based on what the user is doing
    
    switch (state){
        case 0:
            currentState.setString("Place Node or Choose an Option");
            break;
        case 1:
            currentState.setString("Please Choose an Origin Node:");
            break;
        case 2:
            currentState.setString("Please Choose an Origin Node:");
            break;
        case 3:
            currentState.setString("Please Choose a Target Node:");
            break;
    }
        
}

bool graphAlgos::visit(int node){
    
    // Marks visited node red, briefly sleeps program for visual purposes,
    // returns true if node is the target else false
    
    currentGraph.mark(node, sf::Color::Red);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    display();
    if (node==currentGraph.target) return true;
    return false;
    
}
void graphAlgos::bfsShortestPath(int origin, int target){
    
    // Performs a breadth first search shortest-path finder from origin to target
    
    currentGraph.reset();
    display();
    if (currentGraph.getSize()==0) return;
    
    // Initialize visited and prev vectors, as well as the queue used for bfs
    
    bool target_found = false;
    std::vector<bool> visited(currentGraph.getSize(), false);
    std::vector<int> prev(currentGraph.getSize(), -1);
    std::queue<int> nodeQueue;
    nodeQueue.push(origin);
    
    // Perform Breadth-First-Search
    while (nodeQueue.size() > 0){
        int currNode = nodeQueue.front();
        nodeQueue.pop();
        if (visit(currNode)){
            target_found = true;
            // If target found, backtrack through prev, marking all previous nodes used to reach
            // target until origin is reached
            while (!(currNode==-1)){
                currentGraph.mark(currNode, sf::Color::Blue);
                currNode = prev[currNode];
            }
            break;
        }
        visited[currNode] = true;
        for (int n : currentGraph.neighbors[currNode]){
            if (!visited[n]){
                nodeQueue.push(n);
                prev[n] = currNode;
            }
        }
    }
    
    // Update result based on whether or not target is found
    if (target_found){
        result.setString("Shortest Path to Target \n Node Shown.");
    }
    else{
        result.setString("No Path to Target Node");
    }
}

void graphAlgos::dfs(int origin, int target){
    
    // Performs depth-first-search from the origin node to target
    
    currentGraph.reset();
    display();
    if (currentGraph.getSize()==0) return;
    
    // Initialize visited vector and stack used for search
    bool target_found = false;
    std::vector<bool> visited(currentGraph.getSize(), false);
    std::stack<int> nodeStack;
    nodeStack.push(origin);
    
    // Perform depth-first-search
    while (nodeStack.size() > 0){
        int currNode = nodeStack.top();
        nodeStack.pop();
        if (visit(currNode)){
            currentGraph.mark(currNode, sf::Color::Blue);
            target_found = true;
            break;
        }
        visited[currNode] = true;
        for (int n : currentGraph.neighbors[currNode]){
            if (!visited[n]){
                nodeStack.push(n);
            }
        }
        
    }
    
    // Update result string based on whether target node is found
    if (target_found){
        result.setString("Target Node Found!");
    }
    else{
        result.setString("Target Node not Reachable");
    }
    
}

void graphAlgos::events() {
    
    // Poll events, specifically whether the window is closed or mouse is clicked
    
    sf::Event event;
    while (algoWindow.pollEvent(event)){
        if (event.type == sf::Event::Closed){
            algoWindow.close();
            break;
        }
        if (event.type == sf::Event::MouseButtonPressed){
            handleClicks(event);
            break;
        }
    }
}
void graphAlgos::display() {
    
    // Draw all shapes, text, and lines neccesary on the display
    
    algoWindow.clear(sf::Color::White);
    algoWindow.draw(clearButton);
    algoWindow.draw(dfsButton);
    algoWindow.draw(resetButton);
    algoWindow.draw(bfsButton);
    algoWindow.draw(targetButton);
    algoWindow.draw(clearText);
    algoWindow.draw(dfsText);
    algoWindow.draw(resetText);
    algoWindow.draw(bfsText);
    setState(state);
    algoWindow.draw(currentState);
    algoWindow.draw(targetText);
    algoWindow.draw(result);
    for (int i=0; i<currentGraph.lines.size(); i++){
        algoWindow.draw(currentGraph.lines[i]);
    }
    for (int i=0; i<currentGraph.getSize(); i++){
        algoWindow.draw(currentGraph.shapes[i]);
    }
    for (int i=0; i<currentGraph.getSize(); i++){
        algoWindow.draw(currentGraph.labels[i]);
    }
    algoWindow.display();
}


void graphAlgos::handleClicks(sf::Event& event){
    
    // Handles mouse click events based on mouse position and current state
    
    result.setString("");
    
    // Changes state or clears/resets graph based on button clicked
    if (650 < event.mouseButton.x && 800 > event.mouseButton.x){
        if (50 < event.mouseButton.y && event.mouseButton.y < 90){
            currentGraph.clear();
        }
        else if (120 < event.mouseButton.y && event.mouseButton.y < 160){
            state = 1;
        }
        else if (190 < event.mouseButton.y && event.mouseButton.y < 230){
            state = 2;
        }
        else if (260 < event.mouseButton.y && event.mouseButton.y < 290){
            currentGraph.reset();
        }
        else if (330 < event.mouseButton.y && event.mouseButton.y < 360){
            state = 3;
        }
    }
    
    else{
        
        // If no button is clicked, first check if any of the circles were clicked
        
        bool newCircle = true;
        
        for (int i=0; i<currentGraph.getSize(); i++){
            if (sqrt(pow((currentGraph.shapes[i].getPosition().x - (event.mouseButton.x - 25)), 2) + pow((currentGraph.shapes[i].getPosition().y - (event.mouseButton.y - 25)), 2)) < 25){
                newCircle = false;
                
                // If a circle was clicked, either perform dfs/bfs, set target node, or create new neighbors
                if (state==1){
                    dfs(i, currentGraph.target);
                    state = 0;
                }
                else if (state==2){
                    bfsShortestPath(i, currentGraph.target);
                    state = 0;
                }
                else if (state==3){
                    currentGraph.target = i;
                    currentGraph.shapes[i].setFillColor(sf::Color(200, 200, 200));
                    state = 0;
                }
                else if (currentGraph.currentNeighborCheck == -1){
                    currentGraph.currentNeighborCheck = i;
                }
                else{
                    // If a node is waiting for a neighbor, set the nodes as each others neighbor
                    currentGraph.neighbors[i].push_back(currentGraph.currentNeighborCheck);
                    currentGraph.neighbors[currentGraph.currentNeighborCheck].push_back(i);
                    // Draw the line from one node to the other, and add to currentGraph's lines vector
                    sf::VertexArray newLine(sf::LineStrip, 2);
                    newLine[0].position = sf::Vector2f(currentGraph.shapes[i].getPosition().x + 25, currentGraph.shapes[i].getPosition().y + 25);
                    newLine[0].color = sf::Color::Black;
                    newLine[1].position = sf::Vector2f(currentGraph.shapes[currentGraph.currentNeighborCheck].getPosition().x + 25, currentGraph.shapes[currentGraph.currentNeighborCheck].getPosition().y + 25);
                    newLine[1].color = sf::Color::Black;
                    currentGraph.lines.push_back(newLine);
                    currentGraph.currentNeighborCheck = -1;
                    
                }
            }
        }
        if (newCircle){
            // If an empty spot in the window is clicked, add a new circle at that position
            currentGraph.addCircle(event.mouseButton.x, event.mouseButton.y);
            sf::Text newText;
            newText.setFont(algoFont);
            newText.setString(std::to_string(currentGraph.getSize()));
            newText.setCharacterSize(25);
            newText.setFillColor(sf::Color::White);
            newText.setPosition(event.mouseButton.x - 7, event.mouseButton.y - 15);
            currentGraph.labels.push_back(newText);
        }
    }
}
