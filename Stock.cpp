#include "Stock.h"
#include <iostream>

// simple price table without std::map (parallel arrays)
static const char* PRICE_NAMES[] = {
    "Chocolate", "Vanilla", "Red Velvet", "Lemon",
    "Strawberry Jam", "Cream Cheese", "Chocolate Ganache", "Lemon Curd",
    "Vanilla Buttercream", "Chocolate Buttercream", "Whipped Cream", "Cream Cheese Frosting",
    "Rainbow", "Chocolate", "Gold Flakes", "None"
};
static const int PRICE_VALUES[] = {
    25, 25, 35, 30,
    30, 30, 30, 35,
    20, 20, 25, 30,
    15, 15, 20, 0
};

// constructor - calls initialise stock
Stock::Stock() {
    InitializeStock();
}

// sets up starting amounts of each ingredient
void Stock::InitializeStock() {
    // initialize starting stock quantities - 4 of everything (level 1 easier)
    inventory["Chocolate"] = 4;
    inventory["Vanilla"] = 4;
    inventory["Red Velvet"] = 4;
    inventory["Lemon"] = 4;
    
    inventory["Strawberry Jam"] = 4;
    inventory["Cream Cheese"] = 4;
    inventory["Chocolate Ganache"] = 4;
    inventory["Lemon Curd"] = 4;
    
    inventory["Vanilla Buttercream"] = 4;
    inventory["Chocolate Buttercream"] = 4;
    inventory["Whipped Cream"] = 4;
    inventory["Cream Cheese Frosting"] = 4;
    
    inventory["Rainbow"] = 4;
    inventory["Chocolate"] = 4;
    inventory["Gold Flakes"] = 4;
    inventory["None"] = 999; // always available
    
    // prices are defined globally above; getprice() reads from those arrays
}

// uses one ingredient and reduces count by 1
bool Stock::UseIngredient(const std::string& ingredient) {
    if (HasIngredient(ingredient)) {
        inventory[ingredient]--;
        return true;
    }
    return false;
}

// checks if we have any of this ingredient let
bool Stock::HasIngredient(const std::string& ingredient) const {
    auto it = inventory.find(ingredient);
    return it != inventory.end() && it->second > 0;
}

// returns how many of this ingredient have
int Stock::GetStock(const std::string& ingredient) const {
    auto it = inventory.find(ingredient);
    return (it != inventory.end()) ? it->second : 0;
}

// buys 1 ingredient if player has enough money
bool Stock::BuyIngredient(const std::string& ingredient, int& money) {
    int price = GetPrice(ingredient);
    if (price > 0 && money >= price) {
        money -= price;
        inventory[ingredient]++;
        return true;
    }
    return false;
}

// looks up price
int Stock::GetPrice(const std::string& ingredient) const {
    // search through the parallel arrays defined above
    const int COUNT = 16;
    for (int i = 0; i < COUNT; ++i) {
        if (ingredient == PRICE_NAMES[i]) return PRICE_VALUES[i];
    }
    return 0;
}

// displays stock info
void Stock::DisplayStock(int x, int y) const {
    std::cout << "Stock Display at (" << x << ", " << y << ")" << std::endl;
    // implemented in the raylib version
}

// resets all ingredients to same amount (for level restart)
void Stock::ResetAll(int quantity) {
    // set all known items to quantity (except "none")
    for (auto& kv : inventory) {
        if (kv.first == "None") continue;
        kv.second = quantity;
    }
}
