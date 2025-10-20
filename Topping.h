#ifndef TOPPING_H
#define TOPPING_H

#include "Decorations.h"

class Topping : public Decorations {
 protected:
  std::string topping_type_;  // topping name chosen

 public:
  Topping();
  explicit Topping(const std::string& choice);

  void ApplyDecoration() override;
  std::string GetToppingType() const;
  std::string GetDecorationChoice() const override;
  void SetToppingType(const std::string& choice);  // player sets topping
  void SetDecorationChoice(const std::string& choice) override;
  std::string GetDecorationType() const override;  // returns "topping"
  ~Topping() override = default;
};

#endif