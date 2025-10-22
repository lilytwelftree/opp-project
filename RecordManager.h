#ifndef GAME_STATE_MANAGER_H
#define GAME_STATE_MANAGER_H

#include <string>

// forward declarations to avoid circular dependency
class Game;
class Store;

class RecordManager {
 private:
  std::string fileName;

 public:
  // constructor - stores file name
  RecordManager(const std::string& file);

  // saves game to file
  void saveGame(Game& game, const Store& store_);

  // loads game from file
  void loadGame(Game& game, Store& store_);
};

#endif