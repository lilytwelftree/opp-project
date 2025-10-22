#include "IntroScreen.h"

//constructor - takes references to game state variables
IntroScreen::IntroScreen(int& level, int& time_left) : game_level(level), game_time_left(time_left) {}

//draw a coloured rectangle with border
void IntroScreen::DrawBox(Rectangle rect, Color fill, Color border) {
    DrawRectangleRec(rect, fill);
    DrawRectangleLinesEx(rect, 2, border);
}

//load image for intro screen
void IntroScreen::Init() {
    level1_image = LoadTexture("level1.png");
    level2_image = LoadTexture("level2.png");
    level3_image = LoadTexture("level3.png");
}

// clean up memery used by images
void IntroScreen::Cleanup() {
    UnloadTexture(level1_image);
    UnloadTexture(level2_image);
    UnloadTexture(level3_image);
}

// intro clicks for intro screens
void IntroScreen::HandleIntroInput() {
    Vector2 mouse = GetMousePosition();
    
    // continue button position
    Rectangle btn = {250, static_cast<float>(screen_height/2 + 120), 200, 40};
    
    // check if player clicked the button
    if (CheckCollisionPointRec(mouse, btn) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (intro_step < 3) {
            intro_step++;  // move to next intro screen
        } else {
            // finished intro - move to level transition
            show_intro = false;
            show_level_transition = true;
        }
    }
}

//process clicks on level start/transition screens
void IntroScreen::HandleLevelTransitionInput() {
    Vector2 mouse = GetMousePosition();
    
    // start button position
    Rectangle btn = {225, static_cast<float>(screen_height/2 + 90), 150, 40};
    
    // check if player clickd start button
    if (CheckCollisionPointRec(mouse, btn) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        show_level_transition = false;
        
        // set up timer for this level
        if (game_level == 1) game_time_left = 90;
        else if (game_level == 2) game_time_left = 60;
        else if (game_level == 3) game_time_left = 30;
        
        // if starting level 2, reset progress
        if (game_level == 2) {
            //money, satisfaction, orders_completed reset handled by main game
        }
    }
}

//draw intro screen
//shows the story introduction with 4 different screen
void IntroScreen::DrawIntroScreen() {
    // draw level 1 background image (small sore)
    Rectangle src = {0, 0, (float)level1_image.width, (float)level1_image.height};
    Rectangle dst = {0, 0, (float)screen_width, (float)screen_height};
    DrawTexturePro(level1_image, src, dst, {0, 0}, 0, WHITE);
    
    // draw white story box on the left
    Rectangle box = {50, (float)screen_height/2 - 200, 600, 400};
    DrawRectangleRec(box, {255, 255, 255, 240});
    DrawRectangleLinesEx(box, 3, {200, 200, 200, 255});
    
    // welcome story screens
    if (intro_step == 0) {
        // screen 1: welcome
        DrawText("Welcome to Your Shop", box.x + 44, box.y + 50, 32, {100, 100, 100, 255});
    } else if (intro_step == 1) {
        // screen 2: your story
        DrawText("Welcome to Your Shop", box.x + 44, box.y + 30, 28, {100, 100, 100, 255});
        DrawText("You are a hobby cook that has decided to", box.x + 40, box.y + 100, 20, {150, 150, 150, 255});
        DrawText("take a gamble and build your dream", box.x + 40, box.y + 125, 20, {150, 150, 150, 255});
        DrawText("business, decorating cakes!", box.x + 40, box.y + 150, 20, {150, 150, 150, 255});
    } else if (intro_step == 2) {
        // screen 3: your dream
        DrawText("Welcome to Your Shop", box.x + 44, box.y + 30, 28, {100, 100, 100, 255});
        DrawText("You started with just enough money for a", box.x + 40, box.y + 100, 20, {150, 150, 150, 255});
        DrawText("small shop in your local neighbourhood,", box.x + 40, box.y + 125, 20, {150, 150, 150, 255});
        DrawText("but your life long dream is to run your", box.x + 40, box.y + 150, 20, {150, 150, 150, 255});
        DrawText("store in the middle of central park!", box.x + 40, box.y + 175, 20, {150, 150, 150, 255});
    } else if (intro_step == 3) {
        // screen 4: level 1 goals
        DrawText("Level 1", box.x + 44, box.y + 30, 28, {100, 100, 100, 255});
        DrawText("Your store needs to earn enough revenue", box.x + 40, box.y + 100, 20, {150, 150, 150, 255});
        DrawText("while also getting enough happy customers", box.x + 40, box.y + 125, 20, {150, 150, 150, 255});
        DrawText("for you to be able to level up your store", box.x + 40, box.y + 150, 20, {150, 150, 150, 255});
    }
    
    // draw continue button
    Rectangle btn = {box.x + 200, box.y + 320, 200, 40};
    DrawBox(btn, {255, 182, 193, 255}, {200, 200, 200, 255});
    const char* btnText = (intro_step < 3) ? "Click to Continue" : "Start Game";
    DrawText(btnText, btn.x + 15, btn.y + 12, 18, {100, 100, 100, 255});
}

//draw level transition screen
//show level reqirements and start butto
void IntroScreen::DrawLevelTransitionScreen() {
    // draw appropriate background image for this level
    Texture2D* img = (game_level == 1) ? &level1_image : (game_level == 2) ? &level2_image : &level3_image;
    Rectangle src = {0, 0, (float)img->width, (float)img->height};
    Rectangle dst = {0, 0, (float)screen_width, (float)screen_height};
    DrawTexturePro(*img, src, dst, {0, 0}, 0, WHITE);
    
    // draw white info box on the left
    Rectangle box = {50, (float)screen_height/2 - 150, 500, 300};
    DrawRectangleRec(box, {255, 255, 255, 240});
    DrawRectangleLinesEx(box, 3, {200, 200, 200, 255});
    
    // show different text based on current level
    if (game_level == 1) {
        // level 1: small store
        DrawText("Welcome to Your Shop", box.x + 80, box.y + 30, 28, {100, 100, 100, 255});
        DrawText("Build cakes to serve customers!", box.x + 60, box.y + 70, 20, {150, 150, 150, 255});
        DrawText("Level 1: Local Shop (90 seconds)", box.x + 100, box.y + 100, 18, {150, 150, 150, 255});
        DrawText("Requirements:", box.x + 120, box.y + 130, 18, {150, 150, 150, 255});
        DrawText("• $250 minimum", box.x + 140, box.y + 150, 16, {150, 150, 150, 255});
        DrawText("• 70% satisfaction", box.x + 140, box.y + 170, 16, {150, 150, 150, 255});
    } else if (game_level == 2) {
        // level 2: park store
        DrawText("LEVEL UP!", box.x + 180, box.y + 30, 28, {100, 100, 100, 255});
        DrawText("You've leveled up to the City!", box.x + 60, box.y + 70, 20, {150, 150, 150, 255});
        DrawText("Level 2: City Bakery (60 seconds)", box.x + 80, box.y + 100, 18, {150, 150, 150, 255});
        DrawText("New requirements:", box.x + 120, box.y + 130, 18, {150, 150, 150, 255});
        DrawText("• $1500 minimum", box.x + 140, box.y + 150, 16, {150, 150, 150, 255});
        DrawText("• 80% satisfaction", box.x + 140, box.y + 170, 16, {150, 150, 150, 255});
    } else {
        // level 3: central park
        DrawText("FINAL LEVEL!", box.x + 180, box.y + 30, 28, {100, 100, 100, 255});
        DrawText("You've reached the final level!", box.x + 60, box.y + 70, 20, {150, 150, 150, 255});
        DrawText("Level 3: Central Park (30 seconds)", box.x + 80, box.y + 100, 18, {150, 150, 150, 255});
        DrawText("This is the ultimate challenge!", box.x + 120, box.y + 130, 18, {150, 150, 150, 255});
    }
    
    // draw start button
    Rectangle btn = {box.x + 175, box.y + 240, 150, 40};
    DrawBox(btn, {255, 182, 193, 255}, {200, 200, 200, 255});
    DrawText("START", btn.x + 45, btn.y + 12, 20, {100, 100, 100, 255});
}

// getter methods for main game to check state
bool IntroScreen::IsShowingIntro() const { 
    return show_intro; 
}

bool IntroScreen::IsShowingLevelTransition() const { 
    return show_level_transition; 
}

// method to trigger level transition (called by main game)
void IntroScreen::ShowLevelTransition() { 
    show_intro = false; 
    show_level_transition = true; 
}
