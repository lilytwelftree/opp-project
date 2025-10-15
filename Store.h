#ifndef STORE_H
#define STORE_H

#include <iostream>
#include <string>

class Store {
 private:
  // Store levels
  int level;

  // Store rating
  int rating;

  // Store revenue
  double revenue;

 public:
  // Constructor
  Store();

  // Control plater rating
  void updateRating(int rating);

  // Control player level
  void updateLevel(int level);

  // Control player revenue
  void updateRevenue(double revenue);

  // Check if elligible for upgrade
  bool checkUpdgrade(int rating, double revenue, int level);

  // Control store
  void upgradeStore(bool val);

  //get set
  int getRating();
  int getLevel();
  double getRevenue();
};

#endif

// time, frosting