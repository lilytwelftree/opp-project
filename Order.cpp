// order.cpp
#include "Order.h"
#include "Cake.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// constructor
Order::Order() {
    srand(time(0)); // seed random number generator
    base_cost_ = 0.0;
    GenerateRandomOrder();
}

// generate random cake flavour
string Order::RandomFlavour() {
    vector<string> flavours = {"Chocolate", "Vanilla", "Red Velvet", "Lemon"};
    int index = rand() % flavours.size();
    return flavours[index];
}

// generate random filling
string Order::RandomFilling() {
    vector<string> fillings = {"Strawberry Jam", "Cream Cheese", "Chocolate Ganache", "Lemon Curd"};
    int index = rand() % fillings.size();
    return fillings[index];
}

// generate random frosting
string Order::RandomFrosting() {
    vector<string> frostings = {"Vanilla Buttercream", "Chocolate Buttercream", 
                                "Whipped Cream", "Cream Cheese Frosting"};
    int index = rand() % frostings.size();
    return frostings[index];
}

// generate random sprinkles
string Order::RandomSprinkles() {
    vector<string> sprinkles = {"Rainbow", "Chocolate", "Gold Flakes", "None"};
    int index = rand() % sprinkles.size();
    return sprinkles[index];
}

// generate complete random order
void Order::GenerateRandomOrder() {
    request_flavour_ = RandomFlavour();
    request_filling_ = RandomFilling();
    request_frosting_ = RandomFrosting();
    request_sprinkles_ = RandomSprinkles();

    //Exception handling: run-time error
    if (request_flavour_.empty() || request_filling_.empty() || 
        request_frosting_.empty() || request_sprinkles_.empty()) {
        throw std::runtime_error("Error: Generate Order is empty.");
    }

    base_cost_ = CalculateTotalCost();
}

// calculate total cost based on complexity
double Order::CalculateTotalCost() const {
    double cost = 20.0; // base price
    
    // add costs based on selections
    if (request_flavour_ == "Red Velvet" || request_flavour_ == "Lemon") cost += 5.0;
    if (request_filling_ == "Chocolate Ganache") cost += 8.0;
    else if (request_filling_ != "Strawberry Jam") cost += 5.0;
    if (request_frosting_ == "Cream Cheese Frosting") cost += 7.0;
    else cost += 5.0;
    if (request_sprinkles_ == "Gold Flakes") cost += 10.0;
    else if (request_sprinkles_ != "None") cost += 3.0;
    
    return cost;
}

// check if submitted cake matches order
bool Order::CheckIsMatchCake(const Cake& submitted_cake, int& correct_items) const {
    correct_items = 0;
    int total_items = 4;
    
    if (submitted_cake.GetFlavour() == request_flavour_) correct_items++;
    if (submitted_cake.GetFilling() == request_filling_) correct_items++;
    if (submitted_cake.GetFrosting() == request_frosting_) correct_items++;
    if (submitted_cake.GetSprinkles() == request_sprinkles_) correct_items++;
    
    return (correct_items == total_items);
}

// display order details
void Order::DisplayOrder() const {
    cout << "\n===== customer order =====" << endl;
    cout << "flavour: " << request_flavour_ << endl;
    cout << "filling: " << request_filling_ << endl;
    cout << "frosting: " << request_frosting_ << endl;
    cout << "sprinkles: " << request_sprinkles_ << endl;
    cout << "potential revenue: $" << base_cost_ << endl;
    cout << "=========================\n" << endl;
}

// getters
string Order::GetRequestFlavour() const { return request_flavour_; }
string Order::GetRequestFilling() const { return request_filling_; }
string Order::GetRequestFrosting() const { return request_frosting_; }
string Order::GetRequestSprinkles() const { return request_sprinkles_; }

// destructor
Order::~Order() {
    // nothing to clean up
}