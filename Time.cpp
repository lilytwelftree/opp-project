#include "Time.h"

#include <iostream>

#include "Store.h"

using namespace std;

// constructor
Time::Time() {
  // set initial time of 2 mins
  limit_seconds_ = 120;
  start_time_ = time(0);
}

// start timer
void Time::StartCountdown() { start_time_ = time(0); }

// check if under time limit
bool Time::CheckTimeLimit() const {
  time_t current = time(0);

  // calculate time taken
  time_t taken = difftime(current, start_time_);

  // check if less than limit
  if (taken <= limit_seconds_) {
    return true;
  }

  return false;
}

// update time limit every time level updated
void Time::UpdateTimeLimit(bool val) {
  // use value from store function
  if (val) {
    if (limit_seconds_ > 40) {
      limit_seconds_ -= 15;
    }
  }

  // display
  cout << "New time limit: " << limit_seconds_ << " seconds" << endl;
}

// display time
void Time::DisplayTime() const {
  time_t current = time(0);
  int elapsed = static_cast<int>(difftime(current, start_time_));
  int remaining = limit_seconds_ - elapsed;

  if (remaining < 0) {
    remaining = 0;
  }

  cout << "Time left: " << remaining << " seconds" << endl;
}

// display time is done
std::string Time::AlertTimeExpired() {
  if (!CheckTimeLimit()) {
    return "Time is up!";
  }
  return "Time still left";
}

// set time limit
void Time::SetLimitSeconds(int seconds) {
  // Exception handling: Invalid input
  if (seconds <= 40) {
    throw invalid_argument("Error in time limit.");
  }

  limit_seconds_ = seconds;
}

// set time limit based on store level
void Time::SetTimeLimitByLevel(int level) {
  // start with base time of 180 seconds
  limit_seconds_ = 180;

  // Exception handling: Invalid input
  if (level < 0) {
    throw runtime_error(
        "Error in time limit. Cannot be lesser than 40 seconds.");
  }

  // reduce by 15 seconds for each level above 1
  for (int i = 2; i <= level; i++) {
    if (limit_seconds_ > 40) {  // don't go below 40 seconds
      limit_seconds_ -= 15;
    }
  }

  StartCountdown();
  cout << "Time limit set to " << limit_seconds_ << " seconds for Level "
       << level << endl;
}

// get time limit
int Time::GetLimitSeconds() const {
  return limit_seconds_;
}

int Time::GetSecondsRemaining() const {
  time_t current = time(0);
  int elapsed = static_cast<int>(difftime(current, start_time_));
  int remaining = limit_seconds_ - elapsed;
  return remaining < 0 ? 0 : remaining;
}
