#ifndef CAKE_H
#define CAKE_H

#include <iostream>
#include <string>
#include <vector>

#include "Decorations.h"

class Cake {
 private:
  std::string cake_flavour_;
  std::vector<std::string> decorations_list_;
  std::string current_filling_;
  std::string current_topping_;

 public:
  Cake();
  explicit Cake(const std::string& flavour);

  // flavour controls
  void SetFlavour(const std::string& flavour);
  void RemoveFlavour();

  // add decoration
  void AddDecoration(Decorations* decoration);

  // accessors
  std::string GetFlavour() const;
  std::string GetFilling() const;
  std::string GetTopping() const;

  // removal functions
  void RemoveFilling();
  void RemoveTopping();

  // print summary of cake
  void PrintCakeSummary() const;
};

#endif  // CAKE_H