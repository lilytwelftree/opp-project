#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "Cake.h"
#include "Customer.h"
#include "Time.h"
#include "Store.h"
#include "Order.h"
#include "Filling.h"
#include "Frosting.h"
#include "Sprinkles.h"
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
    
    // game state
    void initializeGame();
    void generateNewCustomer();
    void displayCustomerOrder();
    void displayGameStatus();
    void displayTimeRemaining();
    void processOrderSubmission();
    void calculateAndDisplayResults();
    void checkForLevelUp();
    void displayLevelUpNotification();
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

#endif  // GAME_H
