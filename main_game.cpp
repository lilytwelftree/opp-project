#include <iostream>

#include "Draw.h"
#include "Game.h"

using namespace std;

int main() {
  // Show ASCII art first
  Draw drawer;
  drawer.WelcomeSequence();

  cout << "Would you like to load a saved game? (y/n): ";
  string choice;
  getline(cin, choice);

  const string saveFile = "savedFile.txt";

  if (choice == "y" || choice == "Y" || choice == "Yes") {
    Game game(saveFile);      
    game.loadGameData();  
    game.run();
  } else {
    cout << "press enter to start the game..." << endl;
    cin.get();
    Game game;
    game.run();
  }

  return 0;
}
