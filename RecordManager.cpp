#include "RecordManager.h"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "Customer.h"
#include "Game.h"
#include "Order.h"
#include "Store.h"

using namespace std;

// Constructor: Function to store a file name
RecordManager::RecordManager(const string& file) : fileName(file) {}

// Function to write game details
void RecordManager::saveGame(Game& game, const Store& store_) {
  // Open file to write
  ofstream savedGame(fileName);

  // Exception handling
  if (!savedGame.is_open()) {
    throw runtime_error("Error: Cannot write to file: " + fileName);
  }

  // Write to file for each variables
  savedGame << "Level: " << store_.GetLevel() << " "
            << "Ratings: " << store_.GetRating() << " "
            << "Revenue: " << store_.GetRevenue() << " "
            << "Number of orders completed: " << game.getOrdersCompleted()
            << endl;

  // Close file
  savedGame.close();

  // Display status to user
  cout << "Game progress saved!" << endl;
}

// Function to load game with existing details
void RecordManager::loadGame(Game& game, Store& store_) {
  // Open file to read data
  ifstream load(fileName);

  // Exception handling: run-time error
  if (!load.is_open()) {
    throw runtime_error("Error: Cannot open file for reading: " + fileName);
  }

  int level = 0;
  int rating = 0;
  double revenue = 0.0;
  int noOfOrder = 0;

  load >> level >> rating >> revenue >> noOfOrder;

  if (load.fail()) {
    throw runtime_error("Error: Failed to read data from file.");
  }

  // Load data into Game
  store_.UpdateLevel(level);
  store_.UpdateRating(rating);
  store_.UpdateRevenue(revenue);

  // Display status to user
  cout << "Game data has successfully ben added!" << endl;

  // Close file
  load.close();
}
