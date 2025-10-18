#include "Game.h"
#include <iostream>

using namespace std;

int main() {
    cout << "🎂 cake shop simulation 🎂" << endl;
    cout << "press enter to start the game..." << endl;
    cin.get();
    
    Game game;
    game.run();
    
    return 0;
}
