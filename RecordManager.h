#ifndef GAME_STATE_MANAGER_H
#define GAME_STATE_MANAGER_H

#include <string>

#include "Game.h"

class RecordManager {
 private:
  std::string fileName;

 public:
  // Constructor: Function to store a file name
  RecordManager(const std::string& file);

  // Function to write game details
  void saveGame(Game& game, const Store& store_);

  // Function to load game with existing details
  void loadGame(Game& game, Store& store_);
};

#endif