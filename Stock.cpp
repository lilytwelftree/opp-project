#include "Stock.h"
#include <iostream>

// Simple price table without std::map (parallel arrays)
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

Stock::Stock() {
    InitializeStock();
}

void Stock::InitializeStock() {
    // Initialize starting stock quantities - 4 of everything (Level 1 easier)
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
    inventory["None"] = 999; // Always available
    
    // Prices are defined globally above; GetPrice() reads from those arrays
}

bool Stock::UseIngredient(const std::string& ingredient) {
    if (HasIngredient(ingredient)) {
        inventory[ingredient]--;
        return true;
    }
    return false;
}

bool Stock::HasIngredient(const std::string& ingredient) const {
    auto it = inventory.find(ingredient);
    return it != inventory.end() && it->second > 0;
}

int Stock::GetStock(const std::string& ingredient) const {
    auto it = inventory.find(ingredient);
    return (it != inventory.end()) ? it->second : 0;
}

bool Stock::BuyIngredient(const std::string& ingredient, int& money) {
    int price = GetPrice(ingredient);
    if (price > 0 && money >= price) {
        money -= price;
        inventory[ingredient]++;
        return true;
    }
    return false;
}

int Stock::GetPrice(const std::string& ingredient) const {
    // Linear search through the parallel arrays defined above
    const int COUNT = 16;
    for (int i = 0; i < COUNT; ++i) {
        if (ingredient == PRICE_NAMES[i]) return PRICE_VALUES[i];
    }
    return 0;
}

void Stock::DisplayStock(int x, int y) const {
    std::cout << "Stock Display at (" << x << ", " << y << ")" << std::endl;
    // This will be implemented in the Raylib version
}

void Stock::ResetAll(int quantity) {
    // Set all known items to quantity (except "None")
    for (auto& kv : inventory) {
        if (kv.first == "None") continue;
        kv.second = quantity;
    }
}
