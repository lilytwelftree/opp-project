#include "Filling.h"
#include <iostream>

Filling::Filling() {
    fillingChoice = "None";
}

Filling::Filling(const std::string& choice) {
    fillingChoice = choice;
    decorationChoice = choice;
}

// Apply chosen filling to cake
void Filling::applyDecoration() {
    if (!fillingChoice.empty() && fillingChoice != "None") {
        std::cout << "Adding filling: " << fillingChoice << " inside the cake.\n";
    } else {
        std::cout << "No filling selected.\n";
    }
}

// Returns selecteed filling
std::string Filling::getFillingChoice() const {
    return fillingChoice;
}


std::string Filling::getDecorationChoice() const {
    return fillingChoice;
}

// Sets new filling and updates counter
void Filling::setFillingChoice(const std::string& choice) {
    if (AddDecorations()) {
        fillingChoice = choice;
        decorationChoice = choice;
        NoOfDecorations++;
        std::cout << "Filling selected: " << choice << " added successfully.\n";
    } else {
        std::cout << "Cannot add more fillings, decoration limit reached.\n";
    }
}

void Filling::setDecorationChoice(const std::string& choice) {
    setFillingChoice(choice);
}

// Identify decoration type
std::string Filling::getDecorationType() const {
    return "Filling";
}
