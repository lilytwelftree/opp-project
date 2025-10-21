#include "Shop.h"
#include <iostream>

Shop::Shop(Stock* stock_system) : stock(stock_system), shop_open(false) {}

void Shop::OpenShop() {
    shop_open = true;
}

void Shop::CloseShop() {
    shop_open = false;
}

bool Shop::IsOpen() const {
    return shop_open;
}

bool Shop::PurchaseItem(const std::string& ingredient, int& money) {
    if (shop_open && stock) {
        return stock->BuyIngredient(ingredient, money);
    }
    return false;
}

void Shop::DrawShop(int x, int y, int money) const {
    std::cout << "Shop Display at (" << x << ", " << y << ") with $" << money << std::endl;
    // This will be implemented in the Raylib version
}
