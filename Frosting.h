#ifndef FROSTING_H
#define FROSTING_H

#include <iostream>
#include <string>

#include "Decorations.h"

class Frosting : public Decorations {
 protected:
  std::string topping_choice_;

 public:
  // constructor
  Frosting();
  explicit Frosting(const std::string& topping_choice);

  // add pre-set frosting to cake
  void ApplyDecoration() override;

  // specify frosting type to other functions
  std::string GetDecorationChoice() const override;

  // control frosting type selected by player
  void SetDecorationChoice(const std::string& choice) override;

  // identify decoration type
  std::string GetDecorationType() const override;

  // function to add only 1 function
  bool AddFrosting();

  // virtual destructor
  virtual ~Frosting();
};

#endif  // FROSTING_H