#include "Shop.h"
#include <iostream>

// constructor - sets up shop with stock system
Shop::Shop(Stock* stock_system) : stock(stock_system), shop_open(false) {}

// opens the shop
void Shop::OpenShop() {
    shop_open = true;
}

// closes the shop
void Shop::CloseShop() {
    shop_open = false;
}

// checks if shop is open
bool Shop::IsOpen() const {
    return shop_open;
}

// buys an ingredient if shop is open
bool Shop::PurchaseItem(const std::string& ingredient, int& money) {
    if (shop_open && stock) {
        return stock->BuyIngredient(ingredient, money);
    }
    return false;
}

// shows shop on screen
void Shop::DrawShop(int x, int y, int money) const {
    std::cout << "Shop Display at (" << x << ", " << y << ") with $" << money << std::endl;
    // this will be implemented in the raylib version
}
