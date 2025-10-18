#include "Cake.h"

#include <iostream>

#include "Filling.h"
#include "Topping.h"

Cake::Cake() {
  cake_flavour_ = "None";
}

Cake::Cake(const std::string& flavour) {
  cake_flavour_ = flavour;
}

// sets cake flavour
void Cake::SetFlavour(const std::string& flavour) {
  cake_flavour_ = flavour;
  std::cout << "Cake flavour set to: " << cake_flavour_ << "\n";
}

// removes cake flavour
void Cake::RemoveFlavour() {
  cake_flavour_.clear();
  std::cout << "Cake flavour removed.\n";
}

// adds decoration
void Cake::AddDecoration(Decorations* decoration) {
  if (!decoration) {
    std::cout << "Invalid decoration provided.\n";
    return;
  }

  decoration->ApplyDecoration();  // calls correct derived version
  std::string choice = decoration->GetDecorationChoice();

  if (!choice.empty()) {
    decorations_list_.push_back(choice);
  }

  // identify decoration type and store accordingly
  std::string type = decoration->GetDecorationType();
  if (type == "filling") {
    current_filling_ = choice;
  } else if (type == "frosting") {
    current_frosting_ = choice;
  } else if (type == "sprinkles") {
    current_sprinkles_ = choice;
  } else if (type == "topping") {
    current_topping_ = choice;
  }

  std::cout << choice << " added as a " << type << ".\n";
}

// return cake flavour
std::string Cake::GetFlavour() const {
  return cake_flavour_;
}

// return current filling
std::string Cake::GetFilling() const {
  return current_filling_;
}

// return current frosting
std::string Cake::GetFrosting() const {
  return current_frosting_;
}

// return current sprinkles
std::string Cake::GetSprinkles() const {
  return current_sprinkles_;
}

// return current topping
std::string Cake::GetTopping() const {
  return current_topping_;
}

// remove filling from cake
void Cake::RemoveFilling() {
  current_filling_.clear();
  std::cout << "Filling removed.\n";
}

// remove topping from cake
void Cake::RemoveTopping() {
  current_topping_.clear();
  std::cout << "Topping removed.\n";
}

// print cake summary to terminal
void Cake::PrintCakeSummary() const {
  std::cout << "\n Cake Summary \n";
  std::cout << "Flavour: " << (cake_flavour_.empty() ? "None" : cake_flavour_) << "\n";
  std::cout << "Filling: " << (current_filling_.empty() ? "None" : current_filling_) << "\n";
  std::cout << "Frosting: " << (current_frosting_.empty() ? "None" : current_frosting_) << "\n";
  std::cout << "Sprinkles: " << (current_sprinkles_.empty() ? "None" : current_sprinkles_) << "\n";
  std::cout << "Topping: " << (current_topping_.empty() ? "None" : current_topping_) << "\n";
}