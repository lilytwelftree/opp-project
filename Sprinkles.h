#ifndef SPRINKLES_H
#define SPRINKLES_H

#include <string>

#include "Decorations.h"

class Sprinkles : public Decorations {
 protected:
  std::string topping_choice_;

 public:
  // constructor
  Sprinkles();
  explicit Sprinkles(const std::string& choice);

  // add pre-set sprinkles to cake
  void ApplyDecoration() override;

  // specify sprinkles type to other functions
  std::string GetDecorationChoice() const override;

  // control sprinkles type selected by player
  void SetDecorationChoice(const std::string& choice) override;

  // identify decoration type
  std::string GetDecorationType() const override;

  // function to add only 1 sprinkle type
  bool AddSprinkles();

  // virtual destructor
  virtual ~Sprinkles();
};

#endif