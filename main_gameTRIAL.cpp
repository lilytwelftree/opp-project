
#include <iostream>

#include "Draw.h"
#include "Game.h"

using namespace std;

int main() {
  // Show ASCII art first
  Draw drawer;
  drawer.WelcomeSequence();

  cout << "press enter to start the game..." << endl;
  cin.get();

  Game game;
  game.run();

  // Save to text file
  RecordManager recordManager("output.txt");
  recordManager.saveGame(game, game.store_);

  return 0;
}