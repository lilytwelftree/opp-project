#include "Frosting.h"

#include <iostream>
#include <vector>

#include "Store.h"
#include "Time.h"


using namespace std;
// Default contructor
Frosting::Frosting() { toppingChoice = "Vanilla"; }

// Constructor
Frosting::Frosting(string toppingChoice) {
  this->toppingChoice = toppingChoice;
}

// Add pre-set frosting to cake
void Frosting::applyDecoration(){
    //Chnage array name
    if (!toppingChoice.empty()) {
        cout << "Applying frosting: " << toppingChoice << endl;
    } else {
        cout << "No frosting set to apply." << endl;
    }
}

// Specify frosting type to other functions
std::string Frosting::getDecorationChoice() const { 
    //Array name need to change
    if (!toppingChoice.empty()){
    cout << toppingChoice << " frosting was seleted." << endl;
    }
}

// Control frosting type selected by player
void Frosting::setDecorationChoice(const string& choice) {
  if (AddDecorations()) {
    Frosting(toppingChoice);

    //Change to match name of array
    Decorations.push_back();

    //Update no of decorations, change name to amtch decorations
    NoOfDecorations += 1;
    cout << toppingChoice << " frosting was seected!" << endl;
  } else {
    //If array empty
    cout << "Cake is full. Cannot add more frosting!" << endl;
  }
}

// Virtual destructor
Frosting::~Frosting() {
  // Nothing to add
}