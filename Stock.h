#ifndef STOCK_H
#define STOCK_H

#include <string>
#include <map>

class Stock {
private:
    std::map<std::string, int> inventory;
    // Prices are stored using simple parallel data in Stock.cpp (no std::map needed)
    
public:
    Stock();
    
    // Stock management
    void InitializeStock();
    bool UseIngredient(const std::string& ingredient);
    bool HasIngredient(const std::string& ingredient) const;
    int GetStock(const std::string& ingredient) const;
    // Reset all known ingredients to a given quantity ("None" stays large)
    void ResetAll(int quantity);
    
    // Purchasing
    bool BuyIngredient(const std::string& ingredient, int& money);
    int GetPrice(const std::string& ingredient) const;
    
    // Display
    void DisplayStock(int x, int y) const;
};

#endif
