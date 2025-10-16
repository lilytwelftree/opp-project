#ifndef TIME_H
#define TIME_H

#include <ctime>
#include <iostream>
#include <string>
#include "Store.h"

class Time {
 private:
  // Time limit for each attempt
  int limitSeconds;

  // Time taken for each attempt
  std::time_t startTime;

  // Store revenue
  double Revenue;

 public:
  // Contructor
  Time();

  // Start timer
  void startCountdown();

  // Check if under time limit
  bool checkTimeLimit();

  // Update time limit every time level updated
  void updateTimeLimit(bool val);

  // Display time
  void displayTime();

  // Display time is done
  std::string alertTimeExpired();
};

#endif
