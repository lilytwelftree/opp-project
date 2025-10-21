#ifndef SHOP_H
#define SHOP_H

#include "Stock.h"
#include <vector>
#include <string>

class Shop {
private:
    Stock* stock;
    bool shop_open;
    
public:
    Shop(Stock* stock_system);
    
    // Shop control
    void OpenShop();
    void CloseShop();
    bool IsOpen() const;
    
    // Purchasing
    bool PurchaseItem(const std::string& ingredient, int& money);
    
    // Display
    void DrawShop(int x, int y, int money) const;
};

#endif
