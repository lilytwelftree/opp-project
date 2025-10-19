#ifndef STORE_H
#define STORE_H

#include <iostream>
#include <string>

class Store {
 private:
  // store levels
  int level_;

  // store rating
  int rating_;

  // store revenue
  double revenue_;

 public:
  // constructor
  Store();

  // control player rating
  void UpdateRating(int rating);

  // control player level
  void UpdateLevel(int level);

  // control player revenue
  void UpdateRevenue(double revenue);

  // check if eligible for upgrade
  bool CheckUpgrade(int rating, double revenue, int level);

  // control store
  void UpgradeStore(bool val);

  // getters
  int GetRating() const;
  int GetLevel() const;
  double GetRevenue() const;
};

#endif  // STORE_H