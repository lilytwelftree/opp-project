#ifndef FROSTING_H
#define FROSTING_H

#include <iostream>
#include <string>

//Will work once integrated
#include "Decorations.h"

class Frosting: public Decorations {
    protected:
    std::string toppingChoice;

    public:
    //Constructor
    Frosting() = default;

    //Add pre-set frosting to cake
    void applyDecoration() override;

    //Specify frosting type to other functions
    std::string getDecorationChoice() const override;

    //Control frosting type selected by player
    void setDecorationChoice(const std::string& choice) override;

    //Function to add only 1 function
    bool AddFrosting();

    //Virtual destructor
    virtual ~Frosting();
};

#endif
