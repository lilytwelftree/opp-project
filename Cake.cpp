#include "Cake.h"
#include "Filling.h"
#include "Topping.h"
#include <iostream>

Cake::Cake() {
    CakeFlavour = "None";
}

Cake::Cake(const std::string& flavour) {
    CakeFlavour = flavour;
}

// Sets cake flavour
void Cake::setFlavour(const std::string& flavour) {
    CakeFlavour = flavour;
    std::cout << "Cake flavour set to: " << CakeFlavour << "\n";
}

// Removes cake flavour
void Cake::removeFlavour() {
    CakeFlavour.clear();
    std::cout << "Cake flavour removed.\n";
}

// Adds decoration
void Cake::addDecoration(Decorations* decoration) {
    if (!decoration) {
        std::cout << "Invalid decoration provided.\n";
        return;
    }

    decoration->applyDecoration(); // Calls correct derived version
    std::string choice = decoration->getDecorationChoice();

    if (!choice.empty())
        DecorationsList.push_back(choice);

    // Identify decoration type and store accordingly
    std::string type = decoration->getDecorationType();
    if (type == "Filling") {
        currentFilling = choice;
    } else if (type == "Topping" || type == "Frosting" || type == "Sprinkles") {
        currentTopping = choice;
    }

    std::cout << choice << " added as a " << type << ".\n";
}

// Return cake flavour
std::string Cake::getFlavour() const {
    return CakeFlavour;
}

// Return current filling
std::string Cake::getFilling() const {
    return currentFilling;
}

// Return current topping
std::string Cake::getTopping() const {
    return currentTopping;
}

// Remove filling from cake
void Cake::removeFilling() {
    currentFilling.clear();
    std::cout << "Filling removed.\n";
}

// Remove topping from cake
void Cake::removeToping() {
    currentTopping.clear();
    std::cout << "Topping removed.\n";
}

// Print cake summary to terminal
void Cake::printCakeSummary() const {
    std::cout << "\n Cake Summary \n";
    std::cout << "Flavour: " << (CakeFlavour.empty() ? "None" : CakeFlavour) << "\n";
    std::cout << "Filling: " << (currentFilling.empty() ? "None" : currentFilling) << "\n";
    std::cout << "Topping: " << (currentTopping.empty() ? "None" : currentTopping) << "\n";

    std::cout << "Decorations: ";
    if (DecorationsList.empty()) {
        std::cout << "None\n";
    } else {
        for (const auto& d : DecorationsList)
            std::cout << d << " ";
        std::cout << "\n";
    }
}
