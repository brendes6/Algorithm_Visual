//
//  sorting.cpp
//  Algorithm_Visual
//
//  Created by Brendan Desjardins on 7/30/24.
//

#include "sorting.hpp"

void listValue::setValue(int val){
    // Sets value for listValue object
    value = val;
}

void listValue::setIndex(int ind){
    // Sets index for listValue object
    index = ind;
}

void listValue::setShape(int listSize){
    // Sets shape for listValue object
    // Shape width is based on list size, and height is based on the listValue's value
    // Shape position is based on the shape's index in the list
    
    if (listSize==200){
        shape.setSize(sf::Vector2f(3.6, 5*value));
        shape.setPosition((60 + index*3.6), 450 - 5 * value);
        shape.setFillColor(sf::Color::Black);
    }
    else {
        shape.setSize(sf::Vector2f(12.f, 5*value));
        shape.setPosition((60 + index*12), 450 - 5 * value);
        shape.setFillColor(sf::Color::Black);
    }
}

sf::RectangleShape listValue::getShape(){
    // Returns SFML shape object of a listValue
    
    return shape;
}

sortingAlgos::sortingAlgos()
:algoWindow(sf::VideoMode(840, 620), "Sorting Algorithms"){
    // sortingAlgos() constructor
    // Initializes all buttons used in sorting algorithms window
    // Generates an initial list for the window
    
    selectionButton.setSize(sf::Vector2f(150.f, 40.f));
    selectionButton.setPosition(50, 500);
    selectionButton.setFillColor(sf::Color(200, 200, 200));
    selectionButton.setOutlineColor(sf::Color::Black);
    selectionButton.setOutlineThickness(2.f);
    resetButton.setSize(sf::Vector2f(175.f, 40.f));
    resetButton.setPosition(650, 500);
    resetButton.setFillColor(sf::Color(200, 200, 200));
    resetButton.setOutlineColor(sf::Color::Black);
    resetButton.setOutlineThickness(2.f);
    bubbleButton.setSize(sf::Vector2f(150.f, 40.f));
    bubbleButton.setPosition(50, 560);
    bubbleButton.setFillColor(sf::Color(200, 200, 200));
    bubbleButton.setOutlineColor(sf::Color::Black);
    bubbleButton.setOutlineThickness(2.f);
    insertionButton.setSize(sf::Vector2f(150.f, 40.f));
    insertionButton.setPosition(250, 500);
    insertionButton.setFillColor(sf::Color(200, 200, 200));
    insertionButton.setOutlineColor(sf::Color::Black);
    insertionButton.setOutlineThickness(2.f);
    mergeButton.setSize(sf::Vector2f(150.f, 40.f));
    mergeButton.setPosition(250, 560);
    mergeButton.setFillColor(sf::Color(200, 200, 200));
    mergeButton.setOutlineColor(sf::Color::Black);
    mergeButton.setOutlineThickness(2.f);
    resetButton2.setSize(sf::Vector2f(175.f, 40.f));
    resetButton2.setPosition(650, 560);
    resetButton2.setFillColor(sf::Color(200, 200, 200));
    resetButton2.setOutlineColor(sf::Color::Black);
    resetButton2.setOutlineThickness(2.f);
    listSize = 60;
    generate_list(listSize);
}

void sortingAlgos::run(){
    // run() function
    // Initializes all text used in the window
    // Contains game loop that polls events and updates the display
    sf::Font algoFont;
    if (!algoFont.loadFromFile("/System/Library/Fonts/SFNS.ttf")){
        std::cerr << "Font not found\n";
        return;
    }
    selectionText.setFont(algoFont);
    selectionText.setString("Selection Sort");
    selectionText.setCharacterSize(20);
    selectionText.setFillColor(sf::Color::Black);
    selectionText.setPosition(59.f, 510.f);
    resetText.setFont(algoFont);
    resetText.setString("Generate Size 60 List");
    resetText.setCharacterSize(18);
    resetText.setFillColor(sf::Color::Black);
    resetText.setPosition(652.f, 510.f);
    bubbleText.setFont(algoFont);
    bubbleText.setString("Bubble Sort");
    bubbleText.setCharacterSize(20);
    bubbleText.setFillColor(sf::Color::Black);
    bubbleText.setPosition(59.f, 570.f);
    insertionText.setFont(algoFont);
    insertionText.setString("Insertion Sort");
    insertionText.setCharacterSize(20);
    insertionText.setFillColor(sf::Color::Black);
    insertionText.setPosition(259.f, 510.f);
    mergeText.setFont(algoFont);
    mergeText.setString("Merge Sort");
    mergeText.setCharacterSize(20);
    mergeText.setFillColor(sf::Color::Black);
    mergeText.setPosition(259.f, 570.f);
    resetText2.setFont(algoFont);
    resetText2.setString("Generate Size 200 List");
    resetText2.setCharacterSize(18);
    resetText2.setFillColor(sf::Color::Black);
    resetText2.setPosition(652.f, 570.f);
    
    
    while (algoWindow.isOpen()){
        events();
        display();
    }
}

void sortingAlgos::handleClicks(sf::Event& event){
    if (500 < event.mouseButton.y && 540 > event.mouseButton.y){
        if (50 < event.mouseButton.x && event.mouseButton.x < 200){
            selectionSort();
        }
        else if (650 < event.mouseButton.x && event.mouseButton.x < 825){
            listSize = 60;
            generate_list(listSize);
        }
        else if (250 < event.mouseButton.x && event.mouseButton.x < 400){
            insertionSort();
        }
    }
    if (560 < event.mouseButton.y && 600 > event.mouseButton.y){
        if (50 < event.mouseButton.x && event.mouseButton.x < 200){
            bubbleSort();
        }
        else if (250 < event.mouseButton.x && event.mouseButton.x < 450){
            mergeSort(0, listSize-1);
        }
        else if (650 < event.mouseButton.x && event.mouseButton.x < 825){
            listSize = 200;
            generate_list(listSize);
        }
        
    }
}


void sortingAlgos::events() {
    // events() function
    // Polls events, due to the function of this program, being only window closes and mouse button clicks.
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

void sortingAlgos::generate_list(int size){
    // generate_list() function
    // Given an integer 'size' (either 60 or 200), generates a list of 'size' elemetns with values between 0 and 75
    // Clears previous rectList and creates 'size' new rectangle objects with random values
    int max = 75;
    srand(time(0));
    list.clear();
    rectList.clear();
    for (int i=0; i<size; i++){
        int r = rand() % max + 1;
        list.push_back(r);
        
        listValue newVal;
        newVal.setIndex(i);
        newVal.setValue(r);
        newVal.setShape(listSize);
        rectList.push_back(newVal);
    }
}


void sortingAlgos::display() {
    // display() function
    // Displays all buttons and text contained in the window
    // Displays all listValues in rectList on the screen
    
    algoWindow.clear(sf::Color::White);
    algoWindow.draw(selectionButton);
    algoWindow.draw(selectionText);
    algoWindow.draw(resetButton);
    algoWindow.draw(resetText);
    algoWindow.draw(resetButton2);
    algoWindow.draw(resetText2);
    algoWindow.draw(bubbleButton);
    algoWindow.draw(bubbleText);
    algoWindow.draw(insertionButton);
    algoWindow.draw(insertionText);
    algoWindow.draw(mergeButton);
    algoWindow.draw(mergeText);
    
    for (int i=0; i<listSize; i++){
        algoWindow.draw(rectList.at(i).getShape());
    }
    algoWindow.display();
}

void sortingAlgos::selectionSort(){
    // selectionSort() algorithm
    // This function takes a basic implementation of selection sort -
    // - and applies it to BOTH the regular list of values and the rectList
    // When list values are swapped, rectList listValue's values are modified and -
    // - their shapes are set to reflect this modification
    // Sleep function is used to display algorithm implementation in 'slow-mo' essentially
    
    for (int i=0; i<listSize; i++){
        int temp = list.at(i);
        int min = 100;
        int ind;
        for (int j=i; j<listSize; j++){
            if (list.at(j)<min){
                min = list.at(j);
                ind = j;
            }
        }
        list[i] = min;
        list[ind] = temp;
        rectList[i].setValue(min);
        rectList[i].setShape(listSize);
        rectList[ind].setValue(temp);
        rectList[ind].setShape(listSize);
        display();
        std::this_thread::sleep_for(std::chrono::milliseconds(15));
        
        
    }
}

void sortingAlgos::bubbleSort(){
    // bubbleSort() algorithm
    // This function implements bubble sort on both the regular list and rectList
    // sleep function is used again to display how values are moved at an interpretable speed
    
    for (int i=0; i<listSize; i++){
        bool done = true;
        for (int j=0; j<listSize-1; j++){
            if (list[j]>list[j+1]){
                int temp = list[j+1];
                list[j+1] = list[j];
                rectList[j+1].setValue(list[j]);
                rectList[j+1].setShape(listSize);
                list[j] = temp;
                rectList[j].setValue(temp);
                rectList[j].setShape(listSize);
                done = false;
                display();
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        }
        if (done) break;
    }
}

void sortingAlgos::insertionSort(){
    // insertionSort() algorithm
    // Implements an insertion sort algorithm on both lists
    // listValue's in rectList are modified and displayed as the algorithm is ran
    
    for (int i = 1; i < listSize; ++i) {
        int curr = list[i];
        int j = i - 1;
        while (j >= 0 && list[j] > curr) {
            list[j + 1] = list[j];
            rectList[j+1].setValue(list[j]);
            rectList[j+1].setShape(listSize);
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            display();
            j -= 1;
        }
        list[j + 1] = curr;
        rectList[j+1].setValue(curr);
        rectList[j+1].setShape(listSize);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        display();
    }
}

void sortingAlgos::merge(int l, int r, int m){
    // merge() function of merge sort
    // Slightly modified to merge rectList objects as well as regular list values
    // No extra space is used for rectList obejcts, rather, changes and merges made in the regular -
    // - list are reflected in the rectList and displayed as the algorithm runs
    
    int n1 = m - l + 1;
    int n2 = r - m;
    
    std::vector<int> L(n1);
    std::vector<int> R(n2);
    
    for (int i=0; i<n1; i++){
        L[i] = list[l+i];
    }
    for (int i=0; i<n2; i++){
        R[i] = list[m+i+1];
    }
    
    int i = 0, j = 0;
    int k = l;
    
    while (i<n1 && j<n2){
        if (L[i] <= R[j]) {
            list[k] = L[i];
            rectList[k].setValue(L[i]);
            rectList[k].setShape(listSize);
            
            i++;
        }
        else {
            list[k] = R[j];
            rectList[k].setValue(L[i]);
            rectList[k].setShape(listSize);
            j++;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(3));
        display();
        k++;
    }
    
    while (i<n1){
        list[k] = L[i];
        rectList[k].setValue(L[i]);
        rectList[k].setShape(listSize);
        k++;
        i++;
    }
    while (j<n2){
        list[k] = R[j];
        rectList[k].setValue(R[j]);
        rectList[k].setShape(listSize);
        k++;
        j++;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(30));
    display();
}

void sortingAlgos::mergeSort(int l, int r){
    // mergeSort() algorithm
    // Algorithm to recursively merge items in a list
    // No changes neccesary considering that the rectList is also being sorted
    if (l >= r)
        return;

    int m = l + (r - l) / 2;
    mergeSort(l, m);
    mergeSort(m + 1, r);
    merge(l, r, m);
}
