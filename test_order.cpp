#include "Order.h"

#include <iostream>

#include "Cake.h"

using namespace std;

Order::Order() {
  request_flavour_ = "Vanilla";
  request_filling_ = "Strawberry";
  request_frosting_ = "Chocolate";
  request_sprinkles_ = "Rainbow";
  base_cost_ = 10.0;
}

Order::~Order() {
  // Basic destructor, nothing fancy
}

void Order::GenerateRandomOrder() {
  // Super basic implementation for testing
  request_flavour_ = "Chocolate";
  request_filling_ = "Jam";
  request_frosting_ = "Vanilla";
  request_sprinkles_ = "Pink";
}

std::string Order::RandomFlavour() {
  return "Vanilla";
}

std::string Order::RandomFilling() {
  return "Strawberry";
}

std::string Order::RandomFrosting() {
  return "Chocolate";
}

std::string Order::RandomSprinkles() {
  return "Rainbow";
}

double Order::CalculateTotalCost() const {
  return base_cost_;
}

bool Order::CheckIsMatchCake(const Cake& submitted_cake, int& correct_items) const {
  correct_items = 0;
  if (submitted_cake.GetFlavour() == request_flavour_) correct_items++;
  if (submitted_cake.GetFilling() == request_filling_) correct_items++;
  if (submitted_cake.GetTopping() == request_frosting_ || submitted_cake.GetTopping() == request_sprinkles_) correct_items++;
  return correct_items > 0;  // at least something matches
}

void Order::DisplayOrder() const {
  cout << "order: " << request_flavour_ << " cake with " << request_filling_
       << " filling, " << request_frosting_ << " frosting, " << request_sprinkles_ << " sprinkles" << endl;
}

std::string Order::GetRequestFlavour() const {
  return request_flavour_;
}

std::string Order::GetRequestFilling() const {
  return request_filling_;
}

std::string Order::GetRequestFrosting() const {
  return request_frosting_;
}

std::string Order::GetRequestSprinkles() const {
  return request_sprinkles_;
}