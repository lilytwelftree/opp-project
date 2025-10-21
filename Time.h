#ifndef TIME_H
#define TIME_H

#include <ctime>
#include <iostream>
#include <string>

#include "Store.h"

class Time {
 private:
  // time limit for each attempt
  int limit_seconds_;

  // time taken for each attempt
  std::time_t start_time_;

  // store revenue (unused but kept for potential future use)
  // double revenue_;

 public:
  // constructor
  Time();

  // start timer
  void StartCountdown();

  // check if under time limit
  bool CheckTimeLimit() const;

  // update time limit every time level updated
  void UpdateTimeLimit(bool val);

  // display time
  void DisplayTime() const;

  // display time is done
  std::string AlertTimeExpired();

  // set time limit
  void SetLimitSeconds(int seconds);

  // set time limit based on store level
  void SetTimeLimitByLevel(int level);

  // get time limit
  int GetLimitSeconds() const;

  // get remaining seconds (non-negative)
  int GetSecondsRemaining() const;
};

#endif