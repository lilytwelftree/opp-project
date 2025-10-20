#ifndef FILLING_H
#define FILLING_H

#include "Decorations.h"

class Filling : public Decorations {
 protected:
  std::string filling_choice_;  // filling selected by player

 public:
  Filling();
  explicit Filling(const std::string& choice);

  void ApplyDecoration() override;
  std::string GetFillingChoice() const;
  std::string GetDecorationChoice() const override;
  void SetFillingChoice(const std::string& choice);  // player sets filling
  void SetDecorationChoice(const std::string& choice) override;
  std::string GetDecorationType() const override;  // returns "filling"
  ~Filling() override = default;
};

#endif