// Customer.cpp
#include "Customer.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Default constructor
Customer::Customer() {
    static int idCounter = 1;
    customerID = idCounter++;
    preferences = Order(); // Generate random order
    timeLimit = Time();
}

// Constructor with ID
Customer::Customer(int id) {
    customerID = id;
    preferences = Order(); // Generate random order
    timeLimit = Time();
}

// Update order request - generates new random order
void Customer::updateRequest() {
    preferences.generateRandomOrder();
    cout << "Customer #" << customerID << " has a new order!" << endl;
}

// Set starting time limit based on store level
void Customer::setTime(int level) {
    int seconds;
    switch(level) {
        case 1: seconds = 180; break; // 3:00
        case 2: seconds = 150; break; // 2:30
        case 3: seconds = 120; break; // 2:00
        case 4: seconds = 90; break;  // 1:30
        default: seconds = 180; break;
    }
    timeLimit.setLimitSeconds(seconds);
    cout << "Time limit set to " << seconds << " seconds for Level " << level << endl;
}

// Calculate and return customer review (1-5 stars)
int Customer::giveReview(int correctItems, int totalItems, int timeRemaining) {
    if (totalItems == 0) return 1; // Prevent division by zero
    
    // Calculate accuracy percentage
    double accuracy = (double)correctItems / totalItems;
    
    // Calculate time bonus (max 1.0 for having time left)
    int totalTime = timeLimit.getLimitSeconds();
    double timeBonus = (totalTime > 0) ? (double)timeRemaining / totalTime : 0.0;
    
    // Rating calculation: 60% accuracy, 40% time bonus
    double rating = (accuracy * 3.0) + (timeBonus * 2.0);
    
    // Convert to 1-5 star scale
    int stars = (int)(rating + 0.5); // Round to nearest integer
    if (stars < 1) stars = 1;
    if (stars > 5) stars = 5;
    
    cout << "Customer #" << customerID << " gives " << stars << " stars!" << endl;
    return stars;
}

// Get customer's order preferences
Order Customer::getPreferences() const {
    return preferences;
}

// Get time limit
Time Customer::getTimeLimit() const {
    return timeLimit;
}

// Get customer ID
int Customer::getCustomerID() const {
    return customerID;
}

// Destructor
Customer::~Customer() {
    // Nothing to clean up
}