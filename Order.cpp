// Order.cpp
#include "Order.h"
#include "Cake.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Constructor
Order::Order() {
    srand(time(0)); // Seed random number generator
    baseCost = 0.0;
    generateRandomOrder();
}

// Generate random cake flavour
string Order::randomFlavour() {
    vector<string> flavours = {"Chocolate", "Vanilla", "Red Velvet", "Lemon"};
    int index = rand() % flavours.size();
    return flavours[index];
}

// Generate random filling
string Order::randomFilling() {
    vector<string> fillings = {"Strawberry Jam", "Cream Cheese", "Chocolate Ganache", "Lemon Curd"};
    int index = rand() % fillings.size();
    return fillings[index];
}

// Generate random frosting
string Order::randomFrosting() {
    vector<string> frostings = {"Vanilla Buttercream", "Chocolate Buttercream", 
                                "Whipped Cream", "Cream Cheese Frosting"};
    int index = rand() % frostings.size();
    return frostings[index];
}

// Generate random sprinkles
string Order::randomSprinkles() {
    vector<string> sprinkles = {"Rainbow", "Chocolate", "Gold Flakes", "None"};
    int index = rand() % sprinkles.size();
    return sprinkles[index];
}

// Generate complete random order
void Order::generateRandomOrder() {
    requestFlavour = randomFlavour();
    requestFilling = randomFilling();
    requestFrosting = randomFrosting();
    requestSprinkles = randomSprinkles();
    baseCost = calculateTotalCost();
}

// Calculate total cost based on complexity
double Order::calculateTotalCost() const {
    double cost = 20.0; // Base price
    
    // Add costs based on selections
    if (requestFlavour == "Red Velvet" || requestFlavour == "Lemon") cost += 5.0;
    if (requestFilling == "Chocolate Ganache") cost += 8.0;
    else if (requestFilling != "Strawberry Jam") cost += 5.0;
    if (requestFrosting == "Cream Cheese Frosting") cost += 7.0;
    else cost += 5.0;
    if (requestSprinkles == "Gold Flakes") cost += 10.0;
    else if (requestSprinkles != "None") cost += 3.0;
    
    return cost;
}

// Check if submitted cake matches order
bool Order::checkIsMatchCake(const Cake& submittedCake, int& correctItems) const {
    correctItems = 0;
    int totalItems = 4;
    
    if (submittedCake.getFlavour() == requestFlavour) correctItems++;
    if (submittedCake.getFilling() == requestFilling) correctItems++;
    if (submittedCake.getFrosting() == requestFrosting) correctItems++;
    if (submittedCake.getSprinkles() == requestSprinkles) correctItems++;
    
    return (correctItems == totalItems);
}

// Display order details
void Order::displayOrder() const {
    cout << "\n===== CUSTOMER ORDER =====" << endl;
    cout << "Flavour: " << requestFlavour << endl;
    cout << "Filling: " << requestFilling << endl;
    cout << "Frosting: " << requestFrosting << endl;
    cout << "Sprinkles: " << requestSprinkles << endl;
    cout << "Potential Revenue: $" << baseCost << endl;
    cout << "=========================\n" << endl;
}

// Getters
string Order::getRequestFlavour() const { return requestFlavour; }
string Order::getRequestFilling() const { return requestFilling; }
string Order::getRequestFrosting() const { return requestFrosting; }
string Order::getRequestSprinkles() const { return requestSprinkles; }

// Destructor
Order::~Order() {
    // Nothing to clean up
}