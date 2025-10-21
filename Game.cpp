#include "Game.h"

#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <memory>

#include "Draw.h"
#include "RecordManager.h"

using namespace std;

// defaullt constructor
Game::Game()
    : game_running_(false),
      paused_(false),
      orders_completed_(0),
      total_revenue_(0.0),
      level_time_remaining_(0),
      level_start_time_(0),
      // De-fault save file
      manager("savedFile.txt") {
  srand(time(0));  // seed random number generator
}

// constructor
Game::Game(const std::string& savedFile)
    : game_running_(false),
      paused_(false),
      orders_completed_(0),
      total_revenue_(0.0),
      level_time_remaining_(0),
      level_start_time_(0),
      // Load new file
      manager(savedFile) {
  srand(time(0));  // seed random number generator
}
// destructor
Game::~Game() {
  // nothing to clean up
}

// initialize game
void Game::initialiseGame() {
  cout << "\n" << string(55, '=') << endl;
  drawer.WelcomeSequence();
  cout << string(55, '=') << endl;
  cout << "game initialized at store level 1" << endl;
  cout << "Starting metrics:" << endl;
  cout << "Revenue: $0" << endl;
  cout << "Customer satisfaction rating: 0%" << endl;
  cout << "Current level: 1" << endl;
  cout << string(55, '=') << endl;

  game_running_ = true;
  initialiseLevel();
}

// initialize level timing
void Game::initialiseLevel() {
  level_start_time_ = time(nullptr);

  // set level time based on current level
  int current_level = store_.GetLevel();
  switch (current_level) {
    case 1:
      level_time_remaining_ = 180;
      break;  // 3 minutes
    case 2:
      level_time_remaining_ = 240;
      break;  // 4 minutes
    case 3:
      level_time_remaining_ = 300;
      break;  // 5 minutes
    case 4:
      level_time_remaining_ = 360;
      break;  // 6 minutes
    default:
      level_time_remaining_ = 180;
      break;
  }

  cout << "\n" << string(50, '=') << endl;
  cout << "LEVEL " << current_level << " STARTED!" << endl;
  cout << "Time limit: " << level_time_remaining_ << " seconds" << endl;
  cout << "Serve as many customers as possible!" << endl;
  cout << string(50, '=') << endl;

  generateNewCustomer();
}

// generate new customer with random order
void Game::generateNewCustomer() {
  current_customer_ =
      std::unique_ptr<Customer>(new Customer(orders_completed_ + 1));
  current_cake_ = Cake();  // reset cake

  displayCustomerOrder();
}

// display customer order details
void Game::displayCustomerOrder() {
  cout << "\n" << string(50, '-') << endl;
  cout << "new customer #" << current_customer_->GetCustomerID() << " arrived!"
       << endl;
  cout << string(50, '-') << endl;

  Order order = current_customer_->GetPreferences();
  cout << "customer order:" << endl;
  cout << "flavour: " << order.GetRequestFlavour() << endl;
  cout << "filling: " << order.GetRequestFilling() << endl;
  cout << "frosting: " << order.GetRequestFrosting() << endl;
  cout << "sprinkles: " << order.GetRequestSprinkles() << endl;
  cout << "potential revenue: $" << fixed << setprecision(0)
       << order.CalculateTotalCost() << endl;
  cout << string(50, '-') << endl;
}

// display level time remaining
void Game::displayLevelTimeRemaining() {
  int current_time = time(nullptr);
  int elapsed_time = current_time - level_start_time_;
  int remaining_time = level_time_remaining_ - elapsed_time;

  if (remaining_time < 0) remaining_time = 0;

  cout << "Level time remaining: " << remaining_time << " seconds" << endl;
}

// get player actions (real input)
void Game::getPlayerActions() {
  cout << "\n=== BUILD YOUR CAKE ===" << endl;
  cout << "You will now build a cake step by step. Make your choices carefully!"
       << endl;

  // start timer for this order
  Time customer_time = current_customer_->GetTimeLimit();
  customer_time.StartCountdown();

  // get flavour selection
  selectFlavour();

  // get decoration additions
  addFilling();
  addFrosting();
  addSprinkles();

  cout << "\n🎂 Cake completed! Submitting to customer..." << endl;
}

// get flavour selection from player
void Game::selectFlavour() {
  cout << "\n1. CHOOSE CAKE FLAVOUR:" << endl;
  cout << "   [1] Chocolate" << endl;
  cout << "   [2] Vanilla" << endl;
  cout << "   [3] Red Velvet" << endl;
  cout << "   [4] Lemon" << endl;

  int choice;
  bool valid_input = false;

  while (!valid_input) {
    cout << "   Enter choice (1-4): ";
    cin >> choice;
    cin.ignore();  // clear the input buffer

    if (cin.fail()) {
      cin.clear();
      cin.ignore(1000, '\n');
      cout << "   Invalid input. Please enter a number (1-4)." << endl;
      continue;
    }

    if (choice >= 1 && choice <= 4) {
      valid_input = true;
    } else {
      cout << "   Invalid choice. Please enter 1, 2, 3, or 4." << endl;
    }
  }

  string flavour;
  switch (choice) {
    case 1:
      flavour = "Chocolate";
      break;
    case 2:
      flavour = "Vanilla";
      break;
    case 3:
      flavour = "Red Velvet";
      break;
    case 4:
      flavour = "Lemon";
      break;
    default:
      flavour = "Chocolate";
      break;
  }

  current_cake_.SetFlavour(flavour);
  cout << "   ✓ Selected: " << flavour << endl;
  cout << "   Press Enter to continue...";
  cin.get();
}

// get filling selection from player
void Game::addFilling() {
  cout << "\n2. CHOOSE FILLING:" << endl;
  cout << "   [1] Strawberry Jam" << endl;
  cout << "   [2] Cream Cheese" << endl;
  cout << "   [3] Chocolate Ganache" << endl;
  cout << "   [4] Lemon Curd" << endl;

  int choice;
  bool valid_input = false;

  while (!valid_input) {
    cout << "   Enter choice (1-4): ";
    cin >> choice;
    cin.ignore();  // clear the input buffer

    if (cin.fail()) {
      cin.clear();
      cin.ignore(1000, '\n');
      cout << "   Invalid input. Please enter a number (1-4)." << endl;
      continue;
    }

    if (choice >= 1 && choice <= 4) {
      valid_input = true;
    } else {
      cout << "   Invalid choice. Please enter 1, 2, 3, or 4." << endl;
    }
  }

  string filling;
  switch (choice) {
    case 1:
      filling = "Strawberry Jam";
      break;
    case 2:
      filling = "Cream Cheese";
      break;
    case 3:
      filling = "Chocolate Ganache";
      break;
    case 4:
      filling = "Lemon Curd";
      break;
    default:
      filling = "Strawberry Jam";
      break;
  }

  auto filling_obj = std::unique_ptr<Filling>(new Filling(filling));
  current_cake_.AddDecoration(filling_obj.get());
  cout << "   ✓ Selected: " << filling << endl;
  cout << "   Press Enter to continue...";
  cin.get();
}

// get frosting selection from player
void Game::addFrosting() {
  cout << "\n3. CHOOSE FROSTING:" << endl;
  cout << "   [1] Vanilla Buttercream" << endl;
  cout << "   [2] Chocolate Buttercream" << endl;
  cout << "   [3] Whipped Cream" << endl;
  cout << "   [4] Cream Cheese Frosting" << endl;

  int choice;
  bool valid_input = false;

  while (!valid_input) {
    cout << "   Enter choice (1-4): ";
    cin >> choice;
    cin.ignore();  // clear the input buffer

    if (cin.fail()) {
      cin.clear();
      cin.ignore(1000, '\n');
      cout << "   Invalid input. Please enter a number (1-4)." << endl;
      continue;
    }

    if (choice >= 1 && choice <= 4) {
      valid_input = true;
    } else {
      cout << "   Invalid choice. Please enter 1, 2, 3, or 4." << endl;
    }
  }

  string frosting;
  switch (choice) {
    case 1:
      frosting = "Vanilla Buttercream";
      break;
    case 2:
      frosting = "Chocolate Buttercream";
      break;
    case 3:
      frosting = "Whipped Cream";
      break;
    case 4:
      frosting = "Cream Cheese Frosting";
      break;
    default:
      frosting = "Vanilla Buttercream";
      break;
  }

  auto frosting_obj = std::unique_ptr<Frosting>(new Frosting(frosting));
  current_cake_.AddDecoration(frosting_obj.get());
  cout << "   ✓ Selected: " << frosting << endl;
  cout << "   Press Enter to continue...";
  cin.get();
}

// get sprinkles selection from player
void Game::addSprinkles() {
  cout << "\n4. CHOOSE SPRINKLES:" << endl;
  cout << "   [1] Rainbow" << endl;
  cout << "   [2] Chocolate" << endl;
  cout << "   [3] Gold Flakes" << endl;
  cout << "   [4] None" << endl;

  int choice;
  bool valid_input = false;

  while (!valid_input) {
    cout << "   Enter choice (1-4): ";
    cin >> choice;
    cin.ignore();  // clear the input buffer

    if (cin.fail()) {
      cin.clear();
      cin.ignore(1000, '\n');
      cout << "   Invalid input. Please enter a number (1-4)." << endl;
      continue;
    }

    if (choice >= 1 && choice <= 4) {
      valid_input = true;
    } else {
      cout << "   Invalid choice. Please enter 1, 2, 3, or 4." << endl;
    }
  }

  string sprinkles;
  switch (choice) {
    case 1:
      sprinkles = "Rainbow";
      break;
    case 2:
      sprinkles = "Chocolate";
      break;
    case 3:
      sprinkles = "Gold Flakes";
      break;
    case 4:
      sprinkles = "None";
      break;
    default:
      sprinkles = "Rainbow";
      break;
  }

  auto sprinkles_obj = std::unique_ptr<Sprinkles>(new Sprinkles(sprinkles));
  current_cake_.AddDecoration(sprinkles_obj.get());
  cout << "   ✓ Selected: " << sprinkles << endl;
  cout << "   Press Enter to continue...";
  cin.get();
}

// process order submission
void Game::processOrderSubmission() {
  cout << "\n" << string(50, '=') << endl;
  cout << "order submitted!" << endl;
  cout << string(50, '=') << endl;

  // display submitted cake
  cout << "submitted cake:" << endl;
  current_cake_.PrintCakeSummary();

  calculateAndDisplayResults();
}

// calculate and display results
void Game::calculateAndDisplayResults() {
  Order order = current_customer_->GetPreferences();
  int correct_items = 0;

  // check if cake matches order
  bool is_match = order.CheckIsMatchCake(current_cake_, correct_items);

  // calculate time remaining (simulate some time used)
  Time customer_time = current_customer_->GetTimeLimit();
  int time_remaining =
      customer_time.GetLimitSeconds() - 30;  // simulate 30 seconds used
  if (time_remaining < 0) time_remaining = 0;

  // get customer review
  int stars = current_customer_->GiveReview(correct_items, 4, time_remaining);

  // calculate revenue earned
  double revenue_earned = order.CalculateTotalCost() * (correct_items / 4.0);
  total_revenue_ += revenue_earned;

  // update store rating
  int new_rating =
      store_.GetRating() + (stars - 3) * 5;  // adjust rating based on stars
  if (new_rating < 0) new_rating = 0;
  if (new_rating > 100) new_rating = 100;
  store_.UpdateRating(new_rating);

  // display results
  cout << "\nresults:" << endl;
  cout << "customer reaction: ";
  if (stars >= 4)
    cout << "😊 (happy)";
  else if (stars >= 3)
    cout << "😐 (neutral)";
  else
    cout << "😞 (sad)";
  cout << endl;

  cout << "rating: " << stars << " stars" << endl;
  cout << "revenue earned: +$" << fixed << setprecision(0) << revenue_earned
       << endl;
  cout << "overall satisfaction: " << new_rating << "%" << endl;

  orders_completed_++;

  // check for level up
  checkForLevelUp();
}

// check for level up
void Game::checkForLevelUp() {
  int current_level = store_.GetLevel();
  bool should_upgrade = false;

  if (current_level == 1 && total_revenue_ >= 500 && store_.GetRating() >= 70) {
    should_upgrade = true;
  } else if (current_level == 2 && total_revenue_ >= 1500 &&
             store_.GetRating() >= 80) {
    should_upgrade = true;
  } else if (current_level == 3 && total_revenue_ >= 5000 &&
             store_.GetRating() >= 90) {
    should_upgrade = true;
  }

  if (should_upgrade) {
    store_.UpdateLevel(current_level + 1);
    displayLevelUpNotification();
  }
}

// display level up notification
void Game::displayLevelUpNotification() {
  cout << "\n" << string(60, '!') << endl;
  drawer.LevelUp();
  cout << "Now level " << store_.GetLevel() << endl;

  switch (store_.GetLevel()) {
    case 2:
      cout << "new features: more customers, harder orders, higher payments!"
           << endl;
      break;
    case 3:
      cout << "new features: premium customers, complex orders, time pressure!"
           << endl;
      break;
    case 4:
      cout << "ultimate store unlocked! you've mastered the cake business!"
           << endl;
      break;
  }

  cout << string(60, '!') << endl;
}

// check if level time is complete
void Game::checkLevelComplete() {
  int current_time = time(nullptr);
  int elapsed_time = current_time - level_start_time_;
  int remaining_time = level_time_remaining_ - elapsed_time;

  if (remaining_time <= 0) {
    cout << "\n" << string(60, '=') << endl;
    drawer.LevelUp();
    cout << string(60, '=') << endl;

    displayStatistics();

    // check if player can advance to next level
    int current_level = store_.GetLevel();
    bool can_advance = false;

    if (current_level == 1 && total_revenue_ >= 500 &&
        store_.GetRating() >= 70) {
      can_advance = true;
    } else if (current_level == 2 && total_revenue_ >= 1500 &&
               store_.GetRating() >= 80) {
      can_advance = true;
    } else if (current_level == 3 && total_revenue_ >= 5000 &&
               store_.GetRating() >= 90) {
      can_advance = true;
    }

    if (can_advance) {
      store_.UpdateLevel(current_level + 1);
      cout << "\n🎉 LEVEL UP! Moving to Level " << store_.GetLevel() << "!"
           << endl;
      cout << "Press Enter to start the next level...";
      cin.get();
      initialiseLevel();
    } else {
      cout << "\n😞 Not enough progress to advance to next level." << endl;
      cout << "Requirements for Level " << (current_level + 1) << ":" << endl;
      if (current_level == 1) {
        cout << "- Revenue: $500 (you have $" << fixed << setprecision(0)
             << total_revenue_ << ")" << endl;
        cout << "- Rating: 70% (you have " << store_.GetRating() << "%)"
             << endl;
      } else if (current_level == 2) {
        cout << "- Revenue: $1500 (you have $" << fixed << setprecision(0)
             << total_revenue_ << ")" << endl;
        cout << "- Rating: 80% (you have " << store_.GetRating() << "%)"
             << endl;
      } else if (current_level == 3) {
        cout << "- Revenue: $5000 (you have $" << fixed << setprecision(0)
             << total_revenue_ << ")" << endl;
        cout << "- Rating: 90% (you have " << store_.GetRating() << "%)"
             << endl;
      }
      cout << "\nRestarting Level " << current_level << "..." << endl;
      cout << "Press Enter to try again...";
      cin.get();
      initialiseLevel();
    }
  }
}

// check win condition
bool Game::checkWinCondition() {
  return store_.GetLevel() == 4 && store_.GetRating() >= 90;
}

// display victory screen
void Game::displayVictoryScreen() {
  cout << "\n" << string(80, '*') << endl;
  cout << "congratulations! you've won!" << endl;
  cout << "you reached level 4 (ultimate store)" << endl;
  cout << "and maintained >=90% satisfaction rating!" << endl;
  cout << string(80, '*') << endl;

  displayStatistics();

  cout << "\nfinal statistics:" << endl;
  cout << "total orders completed: " << orders_completed_ << endl;
  cout << "total revenue earned: $" << fixed << setprecision(0)
       << total_revenue_ << endl;
  cout << "final satisfaction rating: " << store_.GetRating() << "%" << endl;
  cout << "final store level: " << store_.GetLevel() << endl;

  cout << "\nthank you for playing cake shop!" << endl;
  drawer.GameOver();
}

// display game statistics
void Game::displayStatistics() {
  cout << "\ncurrent statistics:" << endl;
  cout << "orders completed: " << orders_completed_ << endl;
  cout << "total revenue: $" << fixed << setprecision(0) << total_revenue_
       << endl;
  cout << "satisfaction rating: " << store_.GetRating() << "%" << endl;
  cout << "store level: " << store_.GetLevel() << endl;
}

// pause game
void Game::pause() {
  paused_ = true;
  cout << "\ngame paused" << endl;
  cout << "options:" << endl;
  cout << "1. resume" << endl;
  cout << "2. view statistics" << endl;
  cout << "3. exit game" << endl;
}

// resume game
void Game::resume() {
  paused_ = false;
  cout << "game resumed" << endl;
}

// exit game
void Game::exit() {
  game_running_ = false;
  cout << "thanks for playing!" << endl;
}

// main game loop
void Game::run() {
  initialiseGame();

  while (game_running_) {
    // check if level time is up
    checkLevelComplete();

    if (paused_) {
      resume();
    }

    // display level time remaining
    displayLevelTimeRemaining();

    // get player actions step by step
    getPlayerActions();

    // process submission
    processOrderSubmission();

    // check win condition
    if (checkWinCondition()) {
      displayVictoryScreen();
      break;
    }

    // continue to next customer
    cout << "\ncontinuing to next customer..." << endl;
    generateNewCustomer();

    // check if player wants to quit
    cout << "\npress enter to continue (or 'q' to quit)...";
    string input;
    getline(cin, input);
    if (input == "q" || input == "quit") {
      cout << "quitting game..." << endl;
      drawer.GameOver();
      break;
    }
  }
}

// getters
bool Game::isRunning() const { return game_running_; }
bool Game::isPaused() const { return paused_; }
int Game::getOrdersCompleted() const { return orders_completed_; }
double Game::getTotalRevenue() const { return total_revenue_; }

// setter for re-loading game
void Game::setOrdersCompleted(int count) { orders_completed_ = count; }

// Loading data from external file using exception handling to warn us
void Game::loadGameData() {
  try {
    // This* refers to current object game
    manager.loadGame(*this, store_);
    cout << "Game successfully loaded!" << endl;
  } catch (const std::exception& e) {
    cerr << "Failed to load game due to: " << e.what() << endl;
  }
}