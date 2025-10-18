#include "Sprinkles.h"

#include <iostream>

using namespace std;

// default constructor
Sprinkles::Sprinkles() {
  topping_choice_ = "Rainbow";
}

// constructor with choice
Sprinkles::Sprinkles(const string& choice) {
  topping_choice_ = choice;
}

// add pre-set sprinkles to cake
void Sprinkles::ApplyDecoration() {
  if (!topping_choice_.empty()) {
    cout << "Applying sprinkles: " << topping_choice_ << endl;
  } else {
    cout << "No sprinkles set to apply." << endl;
  }
}

// specify sprinkles type to other functions
string Sprinkles::GetDecorationChoice() const {
  if (!topping_choice_.empty()) {
    return topping_choice_;
  }
  return "None";
}

// control sprinkles type selected by player
void Sprinkles::SetDecorationChoice(const string& choice) {
  if (AddDecorations()) {
    topping_choice_ = choice;
    no_of_decorations_ += 1;
    cout << topping_choice_ << " sprinkles were selected!" << endl;
  } else {
    cout << "Cake is full. Can't add more sprinkles!" << endl;
  }
}

// check if sprinkles can be added
bool Sprinkles::AddSprinkles() {
  return AddDecorations();  // use parent class method
}

// virtual destructor
Sprinkles::~Sprinkles() {
  // nothing to clean up
}

// identify decoration type
std::string Sprinkles::GetDecorationType() const {
  return "sprinkles";
}