#ifndef TOPPING_H
#define TOPPING_H

#include "Decorations.h"

class Topping : public Decorations {
protected:
    std::string toppingType; // topping name chosen

public:
    Topping();
    explicit Topping(const std::string& choice);

    void applyDecoration() override; 
    std::string getToppingType() const;
    std::string getDecorationChoice() const override;
    void setToppingType(const std::string& choice); // player sets toppinng
    void setDecorationChoice(const std::string& choice) override;
    std::string getDecorationType() const override; // returns "Topping"
    ~Topping() override = default;
};

#endif
