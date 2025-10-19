#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "RecordManager.h"
#include "Game.h"
#include "Store.h"
#include "Customer.h"
#include "Order.h"

using namespace std;

// Constructor: Function to store a file name
RecordManager::RecordManager(const string& file) : fileName(file) {}

// Function to write game details
void RecordManager::saveGame(Game& game) {
    ofstream savedGame(fileName);  // Changed from ifstream to ofstream
    if (!savedGame.is_open()) {
        throw runtime_error("Error: Cannot write to file: " + fileName);
    }

    int level = game.getLevel();
    int rating = game.getRating();
    int revenue = static_cast<int>(game.getRevenue());

    savedGame << level << endl;
    savedGame << rating << endl;
    savedGame << revenue << endl;


    savedGame.close();
}

// Function to load game with existing details
void RecordManager::loadGame(Game& game) {
    ifstream load(fileName);
    if (!load.is_open()) {
        throw runtime_error("Error: Cannot open file for reading: " + fileName);
    }

    int level;
    int rating;
    double revenue;

    load >> level >> rating >> revenue;

    if (load.fail()) {
        throw runtime_error("Error: Failed to read data from file.");
    }

    // game.setLevel(level);
    // game.setRating(rating);
    // game.setRevenue(revenue);

    load.close();
}
