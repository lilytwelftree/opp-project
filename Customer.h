#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <vector>

#include "Order.h"
#include "Time.h"

class Customer {
 private:
  Time time_limit_;
  Order preferences_;
  int customer_id_;

 public:
  // constructor
  Customer();
  explicit Customer(int id);

  // update order request
  void UpdateRequest();

  // update customer reviews/rating based on cake accuracy and time
  int GiveReview(int correct_items, int total_items, int time_remaining);

  // get customer's order preferences
  Order GetPreferences() const;

  // get time limit
  Time GetTimeLimit() const;

  // get customer id
  int GetCustomerID() const;

  // destructor
  ~Customer();
};

#endif