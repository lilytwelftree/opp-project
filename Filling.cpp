#include "Filling.h"

#include <iostream>

Filling::Filling() {
  filling_choice_ = "None";
}

Filling::Filling(const std::string& choice) {
  filling_choice_ = choice;
  decoration_choice_ = choice;
}

// apply chosen filling to cake
void Filling::ApplyDecoration() {
  if (!filling_choice_.empty() && filling_choice_ != "None") {
    std::cout << "Adding filling: " << filling_choice_ << " inside the cake.\n";
  } else {
    std::cout << "No filling selected.\n";
  }
}

// returns selected filling
std::string Filling::GetFillingChoice() const {
  return filling_choice_;
}

std::string Filling::GetDecorationChoice() const {
  return filling_choice_;
}

// sets new filling and updates counter
void Filling::SetFillingChoice(const std::string& choice) {
  if (AddDecorations()) {
    filling_choice_ = choice;
    decoration_choice_ = choice;
    no_of_decorations_++;
    std::cout << "filling selected: " << choice << " added successfully.\n";
  } else {
    std::cout << "Cake is full can't add more fillings!\n";
  }
}

void Filling::SetDecorationChoice(const std::string& choice) {
  SetFillingChoice(choice);
}

// identify decoration type
std::string Filling::GetDecorationType() const {
  return "filling";
}