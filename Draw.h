#ifndef DRAW_H
#define DRAW_H

#include <string.h>

#include <iostream>

class Draw {
  // Class for all ASCII art
 public:
  // Welcome sequence
  void WelcomeSequence();

  // When leveled up
  void LevelUp();

  // When game over or quit
  void GameOver();

  // Cake
  void CakePic();
};

#endif