// Sprinkles.h
#ifndef SPRINKLES_H
#define SPRINKLES_H

#include <string>
#include "Decorations.h"

class Sprinkles : public Decorations {
protected:
    std::string toppingChoice;
    
public:
    // Constructor
    Sprinkles();
    Sprinkles(const std::string& choice);
    
    // Add pre-set sprinkles to cake
    void applyDecoration() override;
    
    // Specify sprinkles type to other functions
    std::string getDecorationChoice() const override;
    
    // Control sprinkles type selected by player
    void setDecorationChoice(const std::string& choice) override;
    
    // Function to add only 1 sprinkle type
    bool AddSprinkles();
    
    // Virtual destructor
    virtual ~Sprinkles();
};

#endif