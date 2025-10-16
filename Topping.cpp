#include "Topping.h"
#include <iostream>

Topping::Topping() {
    toppingType = "None";
}

Topping::Topping(const std::string& choice) {
    toppingType = choice;
    decorationChoice = choice;
}

// Apply topping to cake
void Topping::applyDecoration() {
    if (!toppingType.empty() && toppingType != "None") {
        std::cout << "Applying topping: " << toppingType << " to the cake.\n";
    } else {
        std::cout << "No topping selected.\n";
    }
}

// Return topping name
std::string Topping::getToppingType() const {
    return toppingType;
}

std::string Topping::getDecorationChoice() const {
    return toppingType;
}

// Sets topping and updates decoration count
void Topping::setToppingType(const std::string& choice) {
    if (AddDecorations()) {
        toppingType = choice;
        decorationChoice = choice;
        NoOfDecorations++;
        std::cout << "Topping chosen: " << choice << " added successfully.\n";
    } else {
        std::cout << "Cannot add more toppings, decoration limit reached.\n";
    }
}

void Topping::setDecorationChoice(const std::string& choice) {
    setToppingType(choice);
}

// Idetnify decoration type
std::string Topping::getDecorationType() const {
    return "Topping";
}
