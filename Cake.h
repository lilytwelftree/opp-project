#ifndef CAKE_H
#define CAKE_H

#include <iostream>
#include <string>
#include <vector>
#include "Decorations.h"

class Cake {
private:
    std::string CakeFlavour;
    std::vector<std::string> DecorationsList;
    std::string currentFilling;
    std::string currentTopping;

public:
    Cake();
    explicit Cake(const std::string& flavour);

    // Flavour controsl
    void setFlavour(const std::string& flavour);
    void removeFlavour();

    // Add decoration
    void addDecoration(Decorations* decoration);

    // Accessors
    std::string getFlavour() const;
    std::string getFilling() const;
    std::string getTopping() const;

    // Removal functions
    void removeFilling();
    void removeToping();

    // Prnit summary of cake
    void printCakeSummary() const;
};

#endif
