#ifndef FILLING_H
#define FILLING_H

#include "Decorations.h"

class Filling : public Decorations {
protected:
    std::string fillingChoice; // filling selected by player

public:
    Filling();
    explicit Filling(const std::string& choice);

    void applyDecoration() override;
    std::string getFillingChoice() const;
    std::string getDecorationChoice() const override;
    void setFillingChoice(const std::string& choice); // player sets filling
    void setDecorationChoice(const std::string& choice) override;
    std::string getDecorationType() const override; // returns "Filling"
    ~Filling() override = default;
};

#endif
