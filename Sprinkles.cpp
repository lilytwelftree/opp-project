// Sprinkles.cpp
#include "Sprinkles.h"
#include <iostream>

using namespace std;

// Default constructor
Sprinkles::Sprinkles() { 
    toppingChoice = "Rainbow"; 
}

// Constructor with choice
Sprinkles::Sprinkles(const string& choice) {
    toppingChoice = choice;
}

// Add pre-set sprinkles to cake
void Sprinkles::applyDecoration() {
    if (!toppingChoice.empty()) {
        cout << "Applying sprinkles: " << toppingChoice << endl;
    } else {
        cout << "No sprinkles set to apply." << endl;
    }
}

// Specify sprinkles type to other functions
string Sprinkles::getDecorationChoice() const {
    if (!toppingChoice.empty()) {
        return toppingChoice;
    }
    return "None";
}

// Control sprinkles type selected by player
void Sprinkles::setDecorationChoice(const string& choice) {
    if (AddDecorations()) {
        toppingChoice = choice;
        NoOfDecorations += 1;
        cout << toppingChoice << " sprinkles were selected!" << endl;
    } else {
        cout << "Cake is full. Cannot add more sprinkles!" << endl;
    }
}

// Check if sprinkles can be added
bool Sprinkles::AddSprinkles() {
    return AddDecorations(); // Use parent class method
}

// Virtual destructor
Sprinkles::~Sprinkles() {
    // Nothing to clean up
}