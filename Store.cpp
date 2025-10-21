#include "Store.h"

#include <iostream>

using namespace std;

// constructor
Store::Store() {
  level_ = 1;
  rating_ = 0;
  revenue_ = 0.0;
}

// control player rating
void Store::UpdateRating(int new_rating) {
  //Exception handling: Invalid input
  if (new_rating < 0){
    throw invalid_argument("Rating cannot be negative.");
  }
  rating_ = new_rating;
}

// control player level
void Store::UpdateLevel(int new_level) {
  //Exception handling: Invalid input
  if (new_level <= 0){
    throw invalid_argument("Error: Levels cannot be negative.");
  }
  level_ = new_level;
}

// control player revenue
void Store::UpdateRevenue(double new_revenue) {
  if (new_revenue <= 0){
    throw invalid_argument("Error: Revenue cannot be negative.");
  }
  revenue_ += new_revenue;
}

// check if eligible for upgrade
bool Store::CheckUpgrade(int rating, double revenue, int /* level */) {
  // set condtions for upgrade
  int rating_limit = 4;
  double money_limit = 15.0;

  if (rating >= rating_limit && revenue >= money_limit) {
    return true;
  }
  return false;
}

// control store
void Store::UpgradeStore(bool val) {
  if (val == true) {
    level_++;
    // add new customers from customer class

    cout << "Store upgraded to Level " << level_ << endl;

    // reset rating
    rating_ = 0;
  } else {
    cout << "Upgrade conditions not met yet! Keep trying!" << endl;
  }
}

// getters
int Store::GetRating() const {
  return rating_;
}

int Store::GetLevel() const {
  return level_;
}

double Store::GetRevenue() const {
  return revenue_;
}