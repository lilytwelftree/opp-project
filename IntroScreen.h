//intro screen handler
//manages the story introduction sequence and level transition screens

#ifndef INTROSCREEN_H
#define INTROSCREEN_H

#include "raylib.h"
#include <string>

class IntroScreen {
private:
    // intro screens
    int intro_step = 0;           // which intro screen to show (0-3)
    bool show_intro = true;       // whether to show introduction screens
    bool show_level_transition = false;  // whether to show level up screen
    
    // level 1 images
    Texture2D level1_image;     
    // level 2 image
    Texture2D level2_image;
    // level 3 image
    Texture2D level3_image;
    
    // screen dimensions
    int screen_width = 1400;
    int screen_height = 900;
    
    // game state reference
    int& game_level;
    int& game_time_left;
    
    //draw a coloured rectangle with border
    void DrawBox(Rectangle rect, Color fill, Color border);

public:
    //constructor - takes references to game state variables
    IntroScreen(int& level, int& time_left);
    
    //load image for intro screen
    void Init();
    
    // clean up memery used by images
    void Cleanup();
    
    // intro clicks for intro screens
    void HandleIntroInput();
    
    //process clicks on level start/transition screens
    void HandleLevelTransitionInput();
    
    //draw intro screen
    //shows the story introduction with 4 different screen
    void DrawIntroScreen();
    
    //draw level transition screen
    //show level reqirements and start butto
    void DrawLevelTransitionScreen();
    
    // getter methods for main game to check state
    bool IsShowingIntro() const;
    bool IsShowingLevelTransition() const;
    
    // method to trigger level transition (called by main game)
    void ShowLevelTransition();
};

#endif