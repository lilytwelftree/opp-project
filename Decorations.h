#ifndef DECORATIONS_H
#define DECORATIONS_H

#include <iostream>
#include <string>

class Decorations {
protected:
    std::string decorationChoice; // decoration selected
    int NoOfDecorations = 0; // no of decor added
    const int MAX_DECORATIONS = 4; // max decorations per cake

public:
    Decorations() = default;
    virtual ~Decorations() = default;

    virtual void applyDecoration() = 0;
    virtual std::string getDecorationType() const = 0;
    virtual std::string getDecorationChoice() const = 0;
    virtual void setDecorationChoice(const std::string& choice) = 0; // player selection

    // Shared utility functions
    bool AddDecorations(); // check if another decoration can be added
    int getNoOfDecorations() const; // returns no of decorations used

    void showDecorationStatus() const;
};

#endif
