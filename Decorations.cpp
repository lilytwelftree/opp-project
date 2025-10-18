#include "Decorations.h"

#include <iostream>

// returns true if cake can accept another decoration
bool Decorations::AddDecorations() {
  return no_of_decorations_ < kMaxDecorations;
}

// returns how many decorations have been added
int Decorations::GetNoOfDecorations() const {
  return no_of_decorations_;
}

// prints decoration status
void Decorations::ShowDecorationStatus() const {
  std::cout << "current decoration choice: "
            << (decoration_choice_.empty() ? "None" : decoration_choice_)
            << "\ndecorations used: " << no_of_decorations_
            << " / " << kMaxDecorations << std::endl;
}