#include "Topping.h"

#include <iostream>

Topping::Topping() {
  topping_type_ = "None";
}

Topping::Topping(const std::string& choice) {
  topping_type_ = choice;
  decoration_choice_ = choice;
}

// apply topping to cake
void Topping::ApplyDecoration() {
  if (!topping_type_.empty() && topping_type_ != "None") {
    std::cout << "applying topping: " << topping_type_ << " to the cake.\n";
  } else {
    std::cout << "no topping selected.\n";
  }
}

// return topping name
std::string Topping::GetToppingType() const {
  return topping_type_;
}

std::string Topping::GetDecorationChoice() const {
  return topping_type_;
}

// sets topping and updates decoration count
void Topping::SetToppingType(const std::string& choice) {
  if (AddDecorations()) {
    topping_type_ = choice;
    decoration_choice_ = choice;
    no_of_decorations_++;
    std::cout << "Topping chosen: " << choice << " added successfully.\n";
  } else {
    std::cout << "Cake is full. Can't add more toppings!\n";
  }
}

void Topping::SetDecorationChoice(const std::string& choice) {
  SetToppingType(choice);
}

// idetnify decoration type
std::string Topping::GetDecorationType() const {
  return topping_type_;
}