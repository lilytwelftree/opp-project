#include "Customer.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Time.h"

using namespace std;

// constructor
Customer::Customer() {
  static int id_counter = 1;
  customer_id_ = id_counter++;
  preferences_ = Order();  // generate random order
  time_limit_ = Time();
}

// constructor with id
Customer::Customer(int id) {
  //Exception handling: Invalid Input
  if (id <= 0){
    throw std::invalid_argument("Error: Customer ID invalid.");
  }
  customer_id_ = id;
  preferences_ = Order();  // generate random order
  time_limit_ = Time();
}

// update order request - generates new random order
void Customer::UpdateRequest() {
  preferences_.GenerateRandomOrder();
  cout << "Customer #" << customer_id_ << " has a new order!" << endl;
}

// calculate and return customer review (1-5 stars)
int Customer::GiveReview(int correct_items, int total_items, int time_remaining) {
  //Exception handling: Invalid Input
  if (correct_items < 0 || total_items < 0 || time_remaining < 0){
    throw std::invalid_argument("Error: Parameters invalid.");
  }

  if (total_items == 0) return 1;  // prevent division by zero

  // calculate accuracy percentge
  double accuracy = static_cast<double>(correct_items) / total_items;

  // use time class methods directly
  int total_time = time_limit_.GetLimitSeconds();

  //Exception handling: run time
  if (total_time <= 40){
    throw std::runtime_error("Error:Invalid time limit in Customer.");
  }
  
  bool time_expired = !time_limit_.CheckTimeLimit();


  // calculate time bonus based on whether time expired
  double time_bonus = 0.0;
  if (!time_expired && total_time > 0) {
    time_bonus = static_cast<double>(time_remaining) / total_time;
  }

  // rating calculation: 60% accuracy, 40% time bonus
  double rating = (accuracy * 3.0) + (time_bonus * 2.0);

  // convert to 1-5 star scale
  int stars = static_cast<int>(rating + 0.5);  // round to nearest integer
  if (stars < 1) stars = 1;
  if (stars > 5) stars = 5;

  cout << "Customer #" << customer_id_ << " gives " << stars << " stars!" << endl;
  if (time_expired) {
    cout << "Time expired: " << time_limit_.AlertTimeExpired() << endl;
  }
  return stars;
}

// get customer's order preferences
Order Customer::GetPreferences() const {
  return preferences_;
}

// get time limit
Time Customer::GetTimeLimit() const {
  return time_limit_;
}

// get customer id
int Customer::GetCustomerID() const {
  return customer_id_;
}

// destructor
Customer::~Customer() {
  // nothing to clean up
}