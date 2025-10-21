#include "RecordManager.h"

#include <filesystem>
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
  // Create an ofstream object and open a file named "output.txt" for writing
  std::ofstream outputFile("output.txt");

  // Check if the file was successfully opened
  if (outputFile.is_open()) {
    // Write variables with current values
    int level = store_.GetLevel();
    int satisfaction = store_.GetRating();
    int revenue = game.getTotalRevenue();
    int noOfOrders = game.getOrdersCompleted();

    // Save values into file
    outputFile << "Level of player " << level << std::endl;
    outputFile << "Satisfaction score: " << satisfaction << std::endl;
    outputFile << "Revenue: " << revenue << std::endl;
    outputFile << "Number of orders completed: " << noOfOrders << std::endl;

    // Close the file
    outputFile.close();

    std::cout << "Data successfully written to output.txt" << std::endl;
  } else {
    // Print an error message
    std::cerr << "Error: Unable to open file for writing." << std::endl;
  }
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
