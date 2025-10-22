// cake shop game - main game file
// game flow:
// 1. intro screens explaining the story
// 2. level transition screens showing requirements
// 3. gameplay: select ingredients, build cake, sell to customer, repete
// 4. shop: buy ingredients when running low on stock
// 5. level up by meeting money and satisfaction requirements

#include "RaylibGame.h"

// constructor - sets up shop with reference to stock system and intro screen
RaylibSimpleGame::RaylibSimpleGame()
    : intro_screen(game.level, game.time_left), shop(&stock_system) {}

// sets up game window, loads images, and starts first level
void RaylibSimpleGame::Init() {
    // suppress raylib info messages for cleaner terminal output
    SetTraceLogLevel(LOG_NONE);
    
    // start game window with game title
    InitWindow(screen_width, screen_height, "Cake Shop - Full Game");

    // intro screen (loads background images)
    intro_screen.Init();

    // random number generator (for generating random orders)
    srand(time(nullptr));

    // set up the timer based on current level
    time_system.SetTimeLimitByLevel(game.level);

    // create the first customer order
    GenerateNewCustomer();
}

// cleanup - frees memory used by loaded images
void RaylibSimpleGame::Cleanup() { intro_screen.Cleanup(); }

// random order and resets cake-building
void RaylibSimpleGame::GenerateNewCustomer() {
    // generate a new random order using the Order class
    current_order = Order();
    game.order_flavour = current_order.GetRequestFlavour();
    game.order_filling = current_order.GetRequestFilling();
    game.order_frosting = current_order.GetRequestFrosting();
    game.order_sprinkles = current_order.GetRequestSprinkles();
    game.order_revenue = static_cast<int>(current_order.CalculateTotalCost());

    // Reset the cake being built
    current_cake = Cake();
    game.current_flavour = "None";
    game.current_filling = "None";
    game.current_frosting = "None";
    game.current_sprinkles = "None";

    // start at step 1 (choosing flavour)
    current_step = 1;
    show_results = false;
}

// update function - called every frame, handles game logic and input
void RaylibSimpleGame::Update() {
    // Stop if game is over
    if (!game.game_running) return;  

    // handle different game states
    if (intro_screen.IsShowingIntro()) {
        intro_screen.HandleIntroInput(); 
        return;
    }

    if (intro_screen.IsShowingLevelTransition()) {
        intro_screen
            .HandleLevelTransitionInput();
        return;
    }

    // count down the message timer
    if (game.message_timer > 0) {
        game.message_timer--;
    }
    // Update the countdown timer
    game.time_left = time_system.GetSecondsRemaining();

    // check if time ran out
    if (game.time_left <= 0) {
        game.time_left = 0;
        show_results = true;  // Show level completion screen
        result_timer = 0;
    }

    // Handle results screen timing and ability to move to next customer
    if (show_results) {
        result_timer++;
        if (result_timer > 180) {
            show_results = false;
            result_timer = 0;
            GenerateNewCustomer();
        }
    }

    // handle player input during gameplay
    HandleInput();
}

//processes player clicks during active gameplay
void RaylibSimpleGame::HandleInput() {
    Vector2 mouse = GetMousePosition();

    // if showing results screen, only handle next/restart buttons
    if (show_results) {
        Rectangle btn = {static_cast<float>(screen_width / 2 - 75), 760, 150, 40};
        if (CheckCollisionPointRec(mouse, btn) &&
            IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (game.time_left == 0) {
                // time runs out, forced restart level
                RestartLevel();
            } else {
                // order done, go to next customer
                GenerateNewCustomer();
            }
        }
        return;
    }

    // Get the ingredient options for the current step
    vector<string> options;
    string* current_component =
        nullptr;  // point to which part of the cake we're building

    if (current_step == 1) {
        // step 1: choose flavour
        options = {"Chocolate", "Vanilla", "Red Velvet", "Lemon"};
        current_component = &game.current_flavour;
    } else if (current_step == 2) {
        // step 2: choose filling
        options = {"Strawberry Jam", "Cream Cheese", "Chocolate Ganache",
                   "Lemon Curd"};
        current_component = &game.current_filling;
    } else if (current_step == 3) {
        // step 3: choose frosting
        options = {"Vanilla Buttercream", "Chocolate Buttercream",
                   "Whipped Cream", "Cream Cheese Frosting"};
        current_component = &game.current_frosting;
    } else if (current_step == 4) {
        // step 4: choose sprinkles
        options = {"Rainbow", "Chocolate", "Gold Flakes", "None"};
        current_component = &game.current_sprinkles;
    }

    // check if player clicked any ingredient button
    for (size_t i = 0; i < options.size(); i++) {
        Rectangle btn = {470, static_cast<float>(160 + i * 55), 360, 45};

        if (CheckCollisionPointRec(mouse, btn) &&
            IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            string selected = options[i];

            // checl if ingredient in stock
            if (stock_system.HasIngredient(selected)) {
                // in stock - Use it and update the cake
                *current_component = selected;
                stock_system.UseIngredient(selected);

                // update the cake object with the selected ingredient
                if (current_step == 1 && selected != "None") {
                    current_cake.SetFlavour(selected);
                } else if (current_step == 3 && selected != "None") {
                    Frosting frosting(selected);
                    current_cake.AddDecoration(&frosting);
                } else if (current_step == 4 && selected != "None") {
                    Sprinkles spr(selected);
                    current_cake.AddDecoration(&spr);
                }
            } else {
                // out of stock - show error message
                game.message_text =
                    "Uh oh. You have ran out. You can stock up at the store";
                game.message_timer = 180; // show message for 3sec
                *current_component = "None";
            }

            // move to next step  until step 4 and then sell
            current_step++;
            if (current_step > 4) current_step = 4;
        }
    }

    // check if player clicked sell button
    if (current_step == 4 && game.current_sprinkles != "") {
        Rectangle sell_btn = {static_cast<float>(screen_width / 2 - 75), 700, 150,
                              50};
        if (CheckCollisionPointRec(mouse, sell_btn) &&
            IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            ProcessOrder(); 
        }
    }

    // check if player clicked shop button
    Rectangle shop_btn = {static_cast<float>(screen_width - 120), 20, 100, 30};
    if (CheckCollisionPointRec(mouse, shop_btn) &&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        // toggle shop open/closed
        if (shop.IsOpen()) {
            shop.CloseShop();
        } else {
            shop.OpenShop();
        }
    }
}

// process order - compares built cake to customer order and calculates results
void RaylibSimpleGame::ProcessOrder() {
    int matches = 0;
    int satisfaction_delta = 0;

    // make sure cake object has the selected flavour
    if (game.current_flavour != "None") {
        current_cake.SetFlavour(game.current_flavour);
    }

    // use order class to score the cake
    current_order.Score(current_cake, matches, satisfaction_delta);

    // award money (always get full payment regardless of matches)
    game.money += game.order_revenue;
    store_system.UpdateRevenue(game.order_revenue);

    // update satisfaction based on how well cake matched
    game.satisfaction += satisfaction_delta;
    if (game.satisfaction < 0) game.satisfaction = 0; 
    if (game.satisfaction > 100) game.satisfaction = 100;

    // number orders completed goes up 1
    game.orders_completed++;

    // check if player can level up
    if (game.level == 1 && game.money >= 250 && game.satisfaction >= 70) {
        // level 1 done. move to level 2
        game.level = 2;
        game.time_left = 60;
        intro_screen.ShowLevelTransition();
        return;
    } else if (game.level == 2 && game.money >= 1500 &&
               game.satisfaction >= 80) {
        // level 2 complete. move to level 3
        game.level = 3;
        game.time_left = 30;
        intro_screen.ShowLevelTransition();
        return;
    }

    // show results screen
    show_results = true;
    result_timer = 0;
}

// restart level - resets timer and starts new customer (used when time runs out)
void RaylibSimpleGame::RestartLevel() {
    time_system.SetTimeLimitByLevel(game.level);
    game.time_left = time_system.GetLimitSeconds();
    GenerateNewCustomer();
}

// use helper function to draw coloured rectangle with border
void RaylibSimpleGame::DrawBox(Rectangle rect, Color fill, Color border) {
    DrawRectangleRec(rect, fill);
    DrawRectangleLinesEx(rect, 2, border);
}

//render everything to screen based on current game state
void RaylibSimpleGame::Draw() {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    // draw the appropriate screen
    if (intro_screen.IsShowingIntro()) {
        intro_screen.DrawIntroScreen();
    } else if (intro_screen.IsShowingLevelTransition()) {
        intro_screen.DrawLevelTransitionScreen();
    } else {
        // main gameplay screen
        DrawRectangle(0, 0, screen_width, screen_height, {240, 240, 240, 255});
        DrawStatusBar();
        DrawCustomerOrder();
        DrawCakeBuilding();
        DrawCakePreview();
        DrawStockBar();
        DrawShop();

        // show error messages (like "out of stock")
        if (game.message_timer > 0) {
            DrawMessage();
        }

        // show results screen after selling
        if (show_results) {
            DrawResults();
        }
    }

    EndDrawing();
}

// draw status bar. top bar showing time, money, satisfaction, level, and orders completed
void RaylibSimpleGame::DrawStatusBar() {
    // Draw gray background bar across top of screen
    Rectangle bar = {0, 0, (float)screen_width, 80};
    DrawRectangleRec(bar, {240, 240, 240, 255});

    int x = 20;  // X position for status items

    // Time remaining
    DrawBox({(float)x, 15, 150, 50}, WHITE, {200, 200, 200, 255});
    DrawText("Time", x + 10, 23, 16, {100, 100, 100, 255});
    DrawText(to_string(game.time_left).c_str(), x + 10, 45, 18,
             {100, 100, 100, 255});
    x += 160;

    // Money earned
    DrawBox({(float)x, 15, 150, 50}, WHITE, {200, 200, 200, 255});
    DrawText("Money", x + 10, 23, 16, {100, 100, 100, 255});
    DrawText(("$" + to_string(game.money)).c_str(), x + 10, 45, 18,
             {100, 100, 100, 255});
    x += 160;

    // Customer satisfaction
    DrawBox({(float)x, 15, 150, 50}, WHITE, {200, 200, 200, 255});
    DrawText("Satisfaction", x + 10, 23, 16, {100, 100, 100, 255});
    DrawText((to_string(game.satisfaction) + "%").c_str(), x + 10, 45, 18,
             {100, 100, 100, 255});
    x += 160;

    // Current level
    DrawBox({(float)x, 15, 150, 50}, WHITE, {200, 200, 200, 255});
    DrawText("Level", x + 10, 23, 16, {100, 100, 100, 255});
    DrawText(to_string(game.level).c_str(), x + 10, 45, 18,
             {100, 100, 100, 255});
    x += 160;

    // Orders completed
    DrawBox({(float)x, 15, 150, 50}, WHITE, {200, 200, 200, 255});
    DrawText("Orders", x + 10, 23, 16, {100, 100, 100, 255});
    DrawText(to_string(game.orders_completed).c_str(), x + 10, 45, 18,
             {100, 100, 100, 255});

    // Shop button in top right corner
    DrawBox({(float)(screen_width - 150), 15, 120, 50}, {144, 238, 144, 255},
            {100, 150, 100, 255});
    DrawText("Shop", screen_width - 110, 30, 18, {100, 100, 100, 255});
}

// draw customer order. left panel showing what customer wants
void RaylibSimpleGame::DrawCustomerOrder() {
    // Draw pink panel
    Rectangle panel = {30, 100, 420, 300};
    DrawBox(panel, {255, 240, 245, 255}, {200, 200, 200, 255});

    // Panel title
    DrawText("Customer Order", 40, 120, 20, {100, 100, 100, 255});

    // show what customer ordered
    DrawText(("Flavour: " + game.order_flavour).c_str(), 40, 160, 18,
             {100, 100, 100, 255});
    DrawText(("Filling: " + game.order_filling).c_str(), 40, 190, 18,
             {100, 100, 100, 255});
    DrawText(("Frosting: " + game.order_frosting).c_str(), 40, 220, 18,
             {100, 100, 100, 255});
    DrawText(("Sprinkles: " + game.order_sprinkles).c_str(), 40, 250, 18,
             {100, 100, 100, 255});

    // Show how much money this order is worth
    DrawBox({40, 300, 250, 40}, WHITE, {200, 200, 200, 255});
    DrawText("Revenue", 50, 308, 16, {100, 100, 100, 255});
    DrawText(("$" + to_string(game.order_revenue)).c_str(), 50, 325, 18,
             {100, 100, 100, 255});
}

// draw cake building - middle panel where player selcts ingredients
void RaylibSimpleGame::DrawCakeBuilding() {
    // Draw blue panel
    Rectangle panel = {470, 100, 500, 300};
    DrawBox(panel, {240, 248, 255, 255}, {200, 200, 200, 255});

    // Panel title
    DrawText("Decoration Station", 480, 120, 20, {100, 100, 100, 255});

    // Determine which step we're on and what options to show
    string title = "";
    vector<string> options;

    if (current_step == 1) {
        title = "step 1: choose flavour";
        options = {"Chocolate", "Vanilla", "Red Velvet", "Lemon"};
    } else if (current_step == 2) {
        title = "step 2: choose filling";
        options = {"Strawberry Jam", "Cream Cheese", "Chocolate Ganache",
                   "Lemon Curd"};
    } else if (current_step == 3) {
        title = "step 3: choose frosting";
        options = {"Vanilla Buttercream", "Chocolate Buttercream",
                   "Whipped Cream", "Cream Cheese Frosting"};
    } else {
        title = "step 4: choose sprinkles";
        options = {"Rainbow", "Chocolate", "Gold Flakes", "None"};
    }

    // Draw step title
    DrawText(title.c_str(), 480, 150, 16, {100, 100, 100, 255});

    // Draw ingredient option buttons
    for (size_t i = 0; i < options.size(); i++) {
        Rectangle btn = {480, (float)(180 + i * 50), 400, 40};

        // check if this option is currently selected
        bool selected = false;
        if (current_step == 1)
            selected = (game.current_flavour == options[i]);
        else if (current_step == 2)
            selected = (game.current_filling == options[i]);
        else if (current_step == 3)
            selected = (game.current_frosting == options[i]);
        else
            selected = (game.current_sprinkles == options[i]);

        // Change button Colour if selected (pink = selected, white = not selected)
        Color fill = selected ? (Color){255, 182, 193, 255} : WHITE;
        Color border =
            selected ? (Color){255, 218, 185, 255} : (Color){200, 200, 200, 255};
        DrawBox(btn, fill, border);

        // Draw option text (darker if selected)
        Color textColour =
            selected ? (Color){100, 100, 100, 255} : (Color){150, 150, 150, 255};
        DrawText(options[i].c_str(), btn.x + 10, btn.y + 12, 16, textColour);
    }
}

// draw cake preview. right panel showing cake being built
void RaylibSimpleGame::DrawCakePreview() {
    // Draw white panel
    Rectangle panel = {990, 100, 400, 300};
    DrawBox(panel, WHITE, {200, 200, 200, 255});

    // Panel title
    DrawText("Your Cake", 1000, 120, 20, {100, 100, 100, 255});

    // center point for drawing the cake
    int cx = 1190;
    int cy = 220;

    // layer 1: cake base (bottom layer - largest circle)
    // colour changes based on flavour selected but default chocolate
    Color baseColour = BROWN;
    if (game.current_flavour == "Vanilla")
        baseColour = {255, 248, 220, 255};
    else if (game.current_flavour == "Red Velvet")
        baseColour = {139, 69, 19, 255};
    else if (game.current_flavour == "Lemon")
        baseColour = {255, 255, 224, 255};
    DrawCircle(cx, cy, 80, baseColour);

    // layer 2: Filling medium circle overlay
    if (game.current_filling != "None") {
        Color fillColour = WHITE;
        if (game.current_filling.find("Strawberry") != string::npos)
            fillColour = {255, 182, 193, 255};
        else if (game.current_filling.find("Chocolate") != string::npos)
            fillColour = BROWN;
        else if (game.current_filling.find("Lemon") != string::npos)
            fillColour = {255, 255, 224, 255};
        DrawCircle(cx, cy, 60, fillColour);
    }

    // layer 3: Frosting, add dots around the edge
    if (game.current_frosting != "None") {
        Color frostColour = WHITE;
        if (game.current_frosting.find("Chocolate") != string::npos)
            frostColour = BROWN;
        else if (game.current_frosting.find("Cream Cheese") != string::npos)
            frostColour = LIGHTGRAY;

        // Draw 12 frosting dots in a circle
        for (int i = 0; i < 12; i++) {
            float angle = i * 30 * DEG2RAD;
            int x = cx + cos(angle) * 50;
            int y = cy + sin(angle) * 50;
            DrawCircle(x, y, 8, frostColour);
        }
    }

    // Layer 4: sprinkles (small dots on top)
    if (game.current_sprinkles != "None") {
        Color sprinkleColour = RED;
        if (game.current_sprinkles == "Chocolate")
            sprinkleColour = BROWN;
        else if (game.current_sprinkles == "Gold Flakes")
            sprinkleColour = GOLD;

        // Draw 15 sprinkles scattered around
        for (int i = 0; i < 15; i++) {
            float angle = i * 24 * DEG2RAD;
            int x =
            //make sure distance from center
                cx + cos(angle) * (30 + (i % 3) * 10);
            int y = cy + sin(angle) * (30 + (i % 3) * 10);
            DrawCircle(x, y, 3, sprinkleColour);
        }
    }

    // show cake selections as text below the cake design
    DrawText(("Flavour: " + game.current_flavour).c_str(), 1000, 320, 16,
             {100, 100, 100, 255});
    DrawText(("Filling: " + game.current_filling).c_str(), 1000, 345, 16,
             {100, 100, 100, 255});
    DrawText(("Frosting: " + game.current_frosting).c_str(), 1000, 370, 16,
             {100, 100, 100, 255});
    DrawText(("Sprinkles: " + game.current_sprinkles).c_str(), 1000, 395, 16,
             {100, 100, 100, 255});

    // show sell button only when cake is complete (step 4 and sprinkles either chosen or none)
    if (current_step == 4 && game.current_sprinkles != "") {
        DrawBox({(float)(screen_width / 2 - 75), 700, 150, 50}, RED, BLACK);
        DrawText("sell cake", screen_width / 2 - 60, 715, 20, WHITE);
    }
}

// draw shop. overlay panel for buying ingrediants. but only when shop clicked and shop = open
void RaylibSimpleGame::DrawShop() {
    if (!shop.IsOpen()) return;

    // Draw dark overlay behind shop
    DrawRectangle(0, 0, screen_width, screen_height, {0, 0, 0, 150});

    // Draw white shop panel in center
    Rectangle panel = {(float)(screen_width / 2 - 325),
                       (float)(screen_height / 2 - 270), 650, 540};
    DrawRectangleRec(panel, WHITE);
    DrawRectangleLinesEx(panel, 3, {200, 200, 200, 255});

    // shop title
    DrawText("shop - buy stock", panel.x + 200, panel.y + 20, 24,
             {100, 100, 100, 255});

    // Show how much money player has
    DrawText(("Money: $" + to_string(game.money)).c_str(), panel.x + 20,
             panel.y + 60, 18, {100, 100, 100, 255});

    // list of ingredients that can be purchased
    vector<string> items = {"Chocolate",
                            "Vanilla",
                            "Red Velvet",
                            "Lemon",
                            "Strawberry Jam",
                            "Cream Cheese",
                            "Chocolate Ganache",
                            "Lemon Curd",
                            "Vanilla Buttercream",
                            "Chocolate Buttercream",
                            "Whipped Cream",
                            "Cream Cheese Frosting",
                            "Rainbow",
                            "Chocolate",
                            "Gold Flakes"};
    // starting positions for buttons
    int y = 100;
    int x = 20;

    // Draw purchase buttons for each ingredient
    for (size_t i = 0; i < items.size(); i++) {
        int price = stock_system.GetPrice(items[i]);

        // arrange in 2 columns
        if (i % 2 == 1) {
            x = 320;
        } else if (i > 0) {
            x = 20;
            y += 40;
        }

        // create button
        Rectangle btn = {panel.x + x, panel.y + y, 290, 35};

        // button is green if affordable, red if too expensive
        Color btnColour = (game.money >= price) ? (Color){200, 255, 200, 255}
                                               : (Color){255, 200, 200, 255};

        // handle click. purchase if affordable
        if (CheckCollisionPointRec(GetMousePosition(), btn) &&
            IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (game.money >= price) {
                shop.PurchaseItem(items[i], game.money);
            }
        }

        // draw button with item name and price
        DrawBox(btn, btnColour, {150, 150, 150, 255});
        DrawText((items[i] + " - $" + to_string(price)).c_str(), btn.x + 10,
                 btn.y + 10, 14, {100, 100, 100, 255});
    }

    // close button at bottom
    Rectangle closeBtn = {panel.x + (panel.width / 2 - 50),
                          panel.y + panel.height - 50, 100, 30};
    DrawBox(closeBtn, {255, 182, 193, 255}, {200, 200, 200, 255});
    DrawText("close", closeBtn.x + 25, closeBtn.y + 8, 16,
             {100, 100, 100, 255});

    // close button click
    if (CheckCollisionPointRec(GetMousePosition(), closeBtn) &&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        shop.CloseShop();
    }
}

// draw stock bar. bottom bar showing how many of each ingredient are in stock
void RaylibSimpleGame::DrawStockBar() {
    int stockY = screen_height - 120;

    // Ddaw gray background
    Rectangle bar = {0, (float)stockY, (float)screen_width, 120};
    DrawRectangleRec(bar, {240, 240, 240, 255});
    DrawRectangleLinesEx(bar, 2, {200, 200, 200, 255});

    // Bar title
    DrawText("Stock Levels", 30, stockY + 15, 20, {100, 100, 100, 255});

    // define ingredient categories
    vector<string> flavours = {"Chocolate", "Vanilla", "Red Velvet", "Lemon"};
    vector<string> fillings = {"Strawberry Jam", "Cream Cheese",
                               "Chocolate Ganache", "Lemon Curd"};
    vector<string> frostings = {"Vanilla Buttercream", "Chocolate Buttercream",
                                "Whipped Cream", "Cream Cheese Frosting"};
    vector<string> sprinkles = {"Rainbow", "Chocolate", "Gold Flakes"};

    int x = 30;
    int y = stockY + 50;

    // draw flavours section
    DrawText("flavours", x, y - 25, 16, {100, 100, 100, 255});
    for (const string& item : flavours) {
        int count = stock_system.GetStock(item);
        Rectangle sq = {(float)x, (float)y, 70, 30};

        // black if out of stock, yellow if in stock
        Color fillColour =
            (count == 0) ? (Color){50, 50, 50, 255} : (Color){255, 255, 200, 255};
        DrawBox(sq, fillColour, {150, 150, 150, 255});

        // Shortened name (first 6 characters)
        string shortName = item.substr(0, min((size_t)6, item.length()));
        Color textColour = (count == 0) ? WHITE : (Color){100, 100, 100, 255};
        DrawText(shortName.c_str(), sq.x + 5, sq.y + 5, 12, textColour);
        DrawText(to_string(count).c_str(), sq.x + 50, sq.y + 5, 14, textColour);

        x += 80;
    }

    x += 15;

    // draw fillings section
    DrawText("fillings", x, y - 25, 16, {100, 100, 100, 255});
    for (const string& item : fillings) {
        int count = stock_system.GetStock(item);
        Rectangle sq = {(float)x, (float)y, 70, 30};

        // Black if out of stock, peach if in stock
        Color fillColour =
            (count == 0) ? (Color){50, 50, 50, 255} : (Color){255, 218, 185, 255};
        DrawBox(sq, fillColour, {150, 150, 150, 255});

        string shortName = item.substr(0, min((size_t)6, item.length()));
        Color textColour = (count == 0) ? WHITE : (Color){100, 100, 100, 255};
        DrawText(shortName.c_str(), sq.x + 5, sq.y + 5, 12, textColour);
        DrawText(to_string(count).c_str(), sq.x + 50, sq.y + 5, 14, textColour);

        x += 80;
    }

    x += 15;

    // draw frosting section
    DrawText("frosting", x, y - 25, 16, {100, 100, 100, 255});
    for (const string& item : frostings) {
        int count = stock_system.GetStock(item);
        Rectangle sq = {(float)x, (float)y, 70, 30};

        // Black if out of stock, gray if in stock
        Color fillColour =
            (count == 0) ? (Color){50, 50, 50, 255} : (Color){200, 200, 200, 255};
        DrawBox(sq, fillColour, {150, 150, 150, 255});

        string shortName = item.substr(0, min((size_t)6, item.length()));
        Color textColour = (count == 0) ? WHITE : (Color){100, 100, 100, 255};
        DrawText(shortName.c_str(), sq.x + 5, sq.y + 5, 12, textColour);
        DrawText(to_string(count).c_str(), sq.x + 50, sq.y + 5, 14, textColour);

        x += 80;
    }

    x += 15;

    // draw sprinkles section
    DrawText("sprinkles", x, y - 25, 16, {100, 100, 100, 255});
    for (const string& item : sprinkles) {
        int count = stock_system.GetStock(item);
        Rectangle sq = {(float)x, (float)y, 70, 30};

        // Black if out of stock, gray if in stock
        Color fillColour =
            (count == 0) ? (Color){50, 50, 50, 255} : (Color){200, 200, 200, 255};
        DrawBox(sq, fillColour, {150, 150, 150, 255});

        string shortName = item.substr(0, min((size_t)6, item.length()));
        Color textColour = (count == 0) ? WHITE : (Color){100, 100, 100, 255};
        DrawText(shortName.c_str(), sq.x + 5, sq.y + 5, 12, textColour);
        DrawText(to_string(count).c_str(), sq.x + 50, sq.y + 5, 14, textColour);

        x += 80;
    }
}

// draw message - shows error messages like "out of stock" above stock bar
void RaylibSimpleGame::DrawMessage() {
    // Calculate message box position (above stock bar)
    float boxW = 700;
    float boxH = 50;
    float boxX = screen_width / 2 - boxW / 2;
    float boxY =
        screen_height - 120 - boxH - 10;  // 10px margin above stock bar
    Rectangle msgBox = {boxX, boxY, boxW, boxH};

    // Draw white box with red border
    DrawBox(msgBox, {255, 255, 255, 240}, RED);

    // Center the text in the box
    int textW = MeasureText(game.message_text.c_str(), 18);
    DrawText(game.message_text.c_str(), msgBox.x + (msgBox.width - textW) / 2,
             msgBox.y + 15, 18, RED);
}

// draw results - shows overlay after selling cake with match results
void RaylibSimpleGame::DrawResults() {
    // Draw dark overlay
    DrawRectangle(0, 0, screen_width, screen_height, {0, 0, 0, 150});

    // Draw white results box in center
    Rectangle box = {(float)(screen_width / 2 - 200),
                     (float)(screen_height / 2 - 150), 400, 300};
    DrawRectangleRec(box, WHITE);
    DrawRectangleLinesEx(box, 3, BLACK);

    if (game.time_left == 0) {
        // TIME'S UP - Level completion screen
        DrawText("TIME'S UP!", box.x + 120, box.y + 30, 28, RED);
        DrawText("LEVEL COMPLETE", box.x + 110, box.y + 60, 24, BLACK);

        // Show level statistics
        DrawText(("Orders: " + to_string(game.orders_completed)).c_str(),
                 box.x + 50, box.y + 100, 20, BLACK);
        DrawText(("Money: $" + to_string(game.money)).c_str(), box.x + 50,
                 box.y + 120, 20, BLACK);
        DrawText(("Satisfaction: " + to_string(game.satisfaction) + "%").c_str(),
                 box.x + 50, box.y + 140, 20, BLACK);

        // Check if player can level up
        bool canLevelUp = false;
        if (game.level == 1 && game.money >= 250 && game.satisfaction >= 70)
            canLevelUp = true;
        if (game.level == 2 && game.money >= 1500 && game.satisfaction >= 80)
            canLevelUp = true;

        if (canLevelUp) {
            DrawText("LEVEL UP AVAILABLE!", box.x + 80, box.y + 170, 20, GREEN);
        } else {
            DrawText("Requirements not met", box.x + 80, box.y + 170, 20, ORANGE);
        }

        DrawText("Click RESTART LEVEL", box.x + 50, box.y + 220, 16, DARKGRAY);

        // Restart button
        Rectangle btn = {(float)(screen_width / 2 - 75), 760, 150, 40};
        DrawRectangleRec(btn, BLUE);
        DrawRectangleLinesEx(btn, 2, BLACK);
        DrawText("RESTART LEVEL", btn.x + 10, btn.y + 10, 16, WHITE);
    } else {
        // ORDER COMPLETE - Normal order completion
        DrawText("ORDER COMPLETE!", box.x + 100, box.y + 30, 24, BLACK);

        // calculate how many ingredients matched
        int matches = 0;
        if (game.current_flavour == game.order_flavour) matches++;
        if (game.current_filling == game.order_filling) matches++;
        if (game.current_frosting == game.order_frosting) matches++;
        if (game.current_sprinkles == game.order_sprinkles) matches++;

        DrawText(("Matches: " + to_string(matches) + "/4").c_str(), box.x + 50,
                 box.y + 80, 20, BLACK);

        // show reaction based on number of matches
        string reaction = (matches >= 3)   ? "excellent!"
                          : (matches >= 2) ? "okay"
                                           : "poor";
        Color reactionColour = (matches >= 3)   ? GREEN
                              : (matches >= 2) ? ORANGE
                                               : RED;
        DrawText(reaction.c_str(), box.x + 50, box.y + 110, 20, reactionColour);

        // show money earned (always full amount)
        DrawText(("money earned: $" + to_string(game.order_revenue)).c_str(),
                 box.x + 50, box.y + 140, 18, BLACK);
        DrawText("click next customer", box.x + 50, box.y + 180, 16, DARKGRAY);

        // next customer button
        Rectangle btn = {(float)(screen_width / 2 - 75), 760, 150, 40};
        DrawRectangleRec(btn, GREEN);
        DrawRectangleLinesEx(btn, 2, BLACK);
        DrawText("next customer", btn.x + 10, btn.y + 10, 16, WHITE);
    }
}

// run function - main game loop, keeps game running until window is closed
void RaylibSimpleGame::Run() {
    Init();  // Set up window and game

    // Main game loop
    while (!WindowShouldClose() && game.game_running) {
        Update();  // Update game logic
        Draw();    // Render to screen
    }

    Cleanup();      // Free resources
    CloseWindow();  // Close the window
}
