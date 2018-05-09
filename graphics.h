#include <avr/pgmspace.h>
#include <Arduino.h>
#ifndef GRAPHICS
#define GRAPHICS

// ball size in pixels
#define BALL_SIZE 1

// vortex size
#define VORTEX_SIZE 4

// function definitions
void drawBall(byte x, byte y);
void eraseBall(byte x, byte y);
void drawVortex(byte x, byte y);
void flashVortex(byte x, byte y);
void updateTimer(int timeLeft);
void updateScore(byte player, int score);
void drawAstronaut();

#endif
