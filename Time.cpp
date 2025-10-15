#include "Time.h"

#include <iostream>

#include "Store.h"

using namespace std;
// Contructor
Time::Time() {
  // Set initiall time of 2 mins
  limitSeconds = 120;
  startTime = time(0);
}

// Start timer
void Time::startCountdown() { startTime = time(0); }
// Check if under time limit
bool Time::checkTimeLimit() {
  time_t current = time(0);

  // Calculate time taken
  time_t taken = difftime(current, startTime);

  // Check if lesser than limit
  if (taken <= limitSeconds) {
    return true;
  }

  return false;
}

// Update time limit every time level updated
void Time::updateTimeLimit(bool val) {

  //Use value from store function
  if (val) {
    if (limitSeconds > 40) {
      limitSeconds -= 15;
    }
  }

  // display
  cout << "New time limit: " << limitSeconds << " seconds" << endl;
}

// Display time
void Time::displayTime() {
  time_t current = time(0);
  int elapsed = static_cast<int>(difftime(current, startTime));
  int remaining = limitSeconds - elapsed;

  if (remaining < 0) {
    remaining = 0;
  }

  cout << "Time left: " << remaining << " seconds" << endl;
}

// Display time is done
std::string Time::alertTimeExpired() {
  if (!checkTimeLimit()) {
    return "Time is up!";
  }
  return "Time still left";
}