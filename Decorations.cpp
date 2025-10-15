#include "Decorations.h"
#include <iostream>

// Returns true if cake can accept another decoration
bool Decorations::AddDecorations() {
    return NoOfDecorations < MAX_DECORATIONS;
}

// Returns how many decorations have been added
int Decorations::getNoOfDecorations() const {
    return NoOfDecorations;
}

// Prints decoration status
void Decorations::showDecorationStatus() const {
    std::cout << "Current decoration choice: "
              << (decorationChoice.empty() ? "None" : decorationChoice)
              << "\nDecorations used: " << NoOfDecorations
              << " / " << MAX_DECORATIONS << std::endl;
}
