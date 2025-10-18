#include "Decorations.h"

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// returns true if cake can accept another decoration
bool Decorations::AddDecorations() {
  //Check if space in vector to add
  if (no_of_decorations_ < kMaxDecorations){

    //Update count of decorations in implementation

    //Add to vector
    decorationsList.push_back(decoration_choice_);

    //Display output that added to vector
    cout << "Added decoration #" << no_of_decorations_ << " : " << decorationsList.back() << endl;

    return true;
  }
  //If full
  else {
    //Display output full
    cout << "Maximum number of decorations already added." << endl;
    return false;
  }
}

// returns how many decorations have been added
int Decorations::GetNoOfDecorations() const {
  return no_of_decorations_;
}

// prints decoration status
void Decorations::ShowDecorationStatus() const {
  //Display number of decorations used
  cout << "Decoration choice: " << no_of_decorations_ << endl;

  //Display decoration choices
  if (!decorationsList.empty()){
    cout << "Applied: " << endl;

    //Use loop to print each decoration, using static cast to convert unsigined int from size()
    for (int i = 0; i < static_cast<int>(decorationsList.size()); i++){
      cout <<(i+1) << ". " << decorationsList[i] << endl;
    }
  }
  //If no decorations
  else{
    cout << "No decorations have been applied yet." << endl;
  }
}