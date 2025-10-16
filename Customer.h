// Customer.h
#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <vector>
#include "Order.h"
#include "Time.h"

class Customer {
private:
    Time timeLimit;
    Order preferences;
    int customerID;
    
public:
    // Constructor
    Customer();
    Customer(int id);
    
    // Update order request
    void updateRequest();
    
    // Set starting time limit based on store level
    void setTime(int level);
    
    // Update customer reviews/rating based on cake accuracy and time
    int giveReview(int correctItems, int totalItems, int timeRemaining);
    
    // Get customer's order preferences
    Order getPreferences() const;
    
    // Get time limit
    Time getTimeLimit() const;
    
    // Get customer ID
    int getCustomerID() const;
    
    // Destructor
    ~Customer();
};

#endif