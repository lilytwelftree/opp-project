#include "Game.h"
#include "Draw.h"
#include <iostream>

using namespace std;

int main() {
    // Show ASCII art first
    Draw drawer;
    drawer.WelcomeSequence();

    cout << "press enter to start the game..." << endl;
    cin.get();
    
    Game game;
    game.run();
    
    return 0;
}
