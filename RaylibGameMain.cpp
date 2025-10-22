#include <ctime>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "raylib.h"

// include custom game domain classes
#include "Cake.h"         // represents the cake being built
#include "Frosting.h"     // frosting decoration type
#include "IntroScreen.h"  // handles intro and level transition screens
#include "Order.h"        // generates customer orders
#include "RaylibGame.h"   // main game class
#include "Shop.h"         // handles purchasing ingredients
#include "Sprinkles.h"    // sprinkles decoration type
#include "Stock.h"        // manages ingredient inventory
#include "Store.h"        // tracks store statistics
#include "Time.h"         // manages countdown timer

using namespace std;

int main() {
    RaylibSimpleGame game;  // Create game object
    game.Run();             // Start the game
    
    // Create an ofstream object and open a file named "output.txt" for writing
    std::ofstream outputFile("output.txt");
  
    // Check if the file was successfully opened
    if (outputFile.is_open()) {
      // Write variables with current values
      int level = game.game.level;
      int satisfaction = game.game.satisfaction;
      int revenue = game.game.money;
      int noOfOrders = game.game.orders_completed;
  
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
    return 0;
}
