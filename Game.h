#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "Cake.h"
#include "Customer.h"
#include "Draw.h"
#include "Filling.h"
#include "Frosting.h"
#include "Order.h"
#include "Sprinkles.h"
#include "Store.h"
#include "Time.h"
#include "Topping.h"

class Game {
 private:
  Store store_;
  std::vector<std::unique_ptr<Customer>> customers_;
  std::unique_ptr<Customer> current_customer_;
  Cake current_cake_;
  bool game_running_;
  bool paused_;
  int orders_completed_;
  double total_revenue_;
  int level_time_remaining_;
  int level_start_time_;

  // To produce ascii
  Draw drawer;

  // game state
  void initialiseGame();
  void initialiseLevel();
  void generateNewCustomer();
  void displayCustomerOrder();
  void displayGameStatus();
  void displayLevelTimeRemaining();
  void processOrderSubmission();
  void calculateAndDisplayResults();
  void checkForLevelUp();
  void displayLevelUpNotification();
  void checkLevelComplete();
  bool checkWinCondition();
  void displayVictoryScreen();

  // player input methods
  void getPlayerActions();
  void selectFlavour();
  void addFilling();
  void addFrosting();
  void addSprinkles();

 public:
  Game();
  ~Game();

  // main game loop
  void run();
  void pause();
  void resume();
  void exit();

  // game statistics
  void displayStatistics();

  // getters
  bool isRunning() const;
  bool isPaused() const;
  int getOrdersCompleted() const;
  double getTotalRevenue() const;
};

#endif
