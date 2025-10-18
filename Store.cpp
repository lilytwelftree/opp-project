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
  rating_ = new_rating;
}

// control player level
void Store::UpdateLevel(int new_level) {
  level_ = new_level;
}

// control player revenue
void Store::UpdateRevenue(double new_revenue) {
  revenue_ += new_revenue;
}

// check if eligible for upgrade
bool Store::CheckUpgrade(int rating, double revenue, int level) {
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