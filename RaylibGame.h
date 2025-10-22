#ifndef RAYLIBGAME_H
#define RAYLIBGAME_H

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
#include "Shop.h"         // handles purchasing ingredients
#include "Sprinkles.h"    // sprinkles decoration type
#include "Stock.h"        // manages ingredient inventory
#include "Store.h"        // tracks store statistics
#include "Time.h"         // manages countdown timer

using namespace std;

/*
 * game state structure
 * holds all the important info about the current game session
 */
struct GameState {
  // timer and progression
  int time_left = 90;  // countdown timer in seconds (starts at 90 for level 1)
  int money = 0;       // total money earned
  int satisfaction = 0;      // customer satisfaction percentage (0-100)
  int level = 1;             // current level (1, 2, or 3)
  int orders_completed = 0;  // number of cakes sold
  bool game_running = true;  // whether game is active

  // current cake being built - tracks what player has selected
  string current_flavour = "None";
  string current_filling = "None";
  string current_frosting = "None";
  string current_sprinkles = "None";

  // customer's order - what they actually want
  string order_flavour = "Chocolate";
  string order_filling = "Strawberry Jam";
  string order_frosting = "Vanilla Buttercream";
  string order_sprinkles = "Rainbow";
  int order_revenue = 25;  // how much money this order is worth

  // ui message system - for showing "out of stock" warnings
  string message_text = "";
  int message_timer = 0;  // how long to display the message (in frames)
};

/*
 * main game class
 * handles all game logic, rendering, and user input
 */
class RaylibSimpleGame {
 private:
  // window settings
  int screen_width = 1400;
  int screen_height = 900;

  // gameplay flow control
  int current_step = 1;       // which ingredient step we're on (1-4)
  bool show_results = false;  // whether to show order completion screen
  int result_timer = 0;       // how long results have been shown

  // intro screen handler
  IntroScreen intro_screen;  // handles intro and level transition screens

  // game domain objects (business logic classes)
  Stock stock_system;   // manages ingredient inventory
  Shop shop;            // handles ingredient purchases
  Order current_order;  // the customer's current order
  Cake current_cake;    // the cake being built
  Store store_system;   // tracks store statistics
  Time time_system;     // manages countdown timer

  /*
   * helper function: draw a colored rectangle with border
   * makes it easy to draw ui boxes throughout the game
   */
  void DrawBox(Rectangle rect, Color fill, Color border);

 public:
  // core game data
  GameState game;  // holds all game state information

  /*
   * constructor
   * sets up the shop with a reference to the stock system and intro screen
   */
  RaylibSimpleGame();

  /*
   * initialization
   * sets up the game window, loads images, and starts the first level
   */
  void Init();

  /*
   * cleanup
   * frees memory used by loaded images
   */
  void Cleanup();

  /*
   * generate new customer
   * creates a new random order and resets the cake-building process
   */
  void GenerateNewCustomer();

  /*
   * update function
   * called every frame - handles game logic and input
   */
  void Update();

  /*
   * handle input
   * processes player clicks during active gameplay
   */
  void HandleInput();

  /*
   * process order
   * compares the built cake to customer order and calculates results
   */
  void ProcessOrder();

  /*
   * restart level
   * resets the timer and starts a new customer (used when time runs out)
   */
  void RestartLevel();

  /*
   * draw function
   * renders everything to the screen based on current game state
   */
  void Draw();

  /*
   * draw status bar
   * top bar showing time, money, satisfaction, level, and orders completed
   */
  void DrawStatusBar();

  /*
   * draw customer order
   * left panel showing what the customer wants
   */
  void DrawCustomerOrder();

  /*
   * draw cake building
   * middle panel where player selcts ingredients
   */
  void DrawCakeBuilding();

  /*
   * draw cake preview
   * right panel showing the cake being built with visual representation
   */
  void DrawCakePreview();

  /*
   * draw shop
   * overlay panel for buying ingrediants (only shows if shop is open)
   */
  void DrawShop();

  /*
   * draw stock bar
   * bottom bar showing how many of each ingredient are in stock
   */
  void DrawStockBar();

  /*
   * draw message
   * shows error messages like "out of stock" above the stock bar
   */
  void DrawMessage();

  /*
   * draw results
   * shows overlay after selling a cake with match results
   */
  void DrawResults();

  /*
   * run function
   * main game loop - keeps game running until window is closed
   */
  void Run();
};

#endif
