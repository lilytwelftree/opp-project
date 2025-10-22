#ifndef SHOP_H
#define SHOP_H

#include "Stock.h"
#include <vector>
#include <string>

class Shop {
private:
    Stock* stock;        // points to the stock system to buy ingredients
    bool shop_open;      // whether the shop is currently open or closed
    
public:
    Shop(Stock* stock_system);
    
    // shop control
    void OpenShop();
    void CloseShop();
    bool IsOpen() const;
    
    // purchasing
    bool PurchaseItem(const std::string& ingredient, int& money);
    
    // display
    void DrawShop(int x, int y, int money) const;
};

#endif
