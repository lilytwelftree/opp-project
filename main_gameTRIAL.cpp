#include <fstream>  // Include fstream for file operations
#include <iostream>

#include "Draw.h"
#include "Game.h"
#include "Store.h"

using namespace std;

int main() {
  // Show ASCII art first
  Draw drawer;
  drawer.WelcomeSequence();

  cout << "press enter to start the game..." << endl;
  cin.get();

  Game game;
  game.run();

  // After game finishes, get stats
  int level = game.getTotalRevenue();
  double orders = game.getOrdersCompleted();

  // Append to "savedGame" file
  ofstream saveFile("savedGame", ios::app);  // open in append mode
  if (!saveFile) {
    cerr << "Error opening savedGame file for writing." << endl;
    return 1;
  }

  // Save in format: level rating  (space separated)
  saveFile << level << " " << orders << endl;

  saveFile.close();

  cout << "Game results saved!" << endl;

  return 0;
}
