#include "Frosting.h"

#include <iostream>
#include <vector>

#include "Store.h"
#include "Time.h"

using namespace std;

// default constructor
Frosting::Frosting() {
  topping_choice_ = "Vanilla";
}

// constructor
Frosting::Frosting(const string& topping_choice) {
  //Exception handling: Empty input
  if (topping_choice.empty()){
    throw invalid_argument("Error:Frosting is empty.");
  }

  this->topping_choice_ = topping_choice;
  decoration_choice_ = topping_choice;
}

// add pre-set frosting to cake
void Frosting::ApplyDecoration() {
  // change array name (old comment)
  if (!topping_choice_.empty()) {
    cout << "applying frosting: " << topping_choice_ << endl;
  } else {
    cout << "no frosting set to apply." << endl;
  }
}

// specify frosting type to other functions
std::string Frosting::GetDecorationChoice() const {
  if (!topping_choice_.empty()) {
    return topping_choice_;
  }
  return "None";
}

// control frosting type selected by player
void Frosting::SetDecorationChoice(const string& choice) {
  if (AddDecorations()) {
    topping_choice_ = choice;
    no_of_decorations_ += 1;
    cout << topping_choice_ << " frosting was selected!" << endl;
  } else {
    // if array empty
    cout << "cake is full. cannot add more frosting!" << endl;
  }
}

// virtual destructor
Frosting::~Frosting() {
  // nothing to add
}

// identify decoration type
std::string Frosting::GetDecorationType() const {
  return "frosting";
}