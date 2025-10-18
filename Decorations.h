#ifndef DECORATIONS_H
#define DECORATIONS_H

#include <iostream>
#include <string>

class Decorations {
 protected:
  std::string decoration_choice_;  // decoration selected
  int no_of_decorations_ = 0;     // no of decor added
  const int kMaxDecorations = 4;   // max decorations per cake

  //Vector of string
  std::vector<std::string> decorationsList;

 public:
  Decorations() = default;
  virtual ~Decorations() = default;

  virtual void ApplyDecoration() = 0;
  virtual std::string GetDecorationType() const = 0;
  virtual std::string GetDecorationChoice() const = 0;
  virtual void SetDecorationChoice(const std::string& choice) = 0;  // player selection

  // shared utility functions
  bool AddDecorations();  // check if another decoration can be added
  int GetNoOfDecorations() const;  // returns no of decorations used

  void ShowDecorationStatus() const;
};

#endif  // DECORATIONS_H