#include "graphics.h"
#include <Arduino.h>
#include <TVout.h>
#include <fontALL.h>

extern TVout tv;

PROGMEM const unsigned char astronaut[] = {
 64, 64,
 0xff, 0xff, 0xff, 0xf0, 0x0f, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xfc, 0x00, 0x00, 0x3f, 0xff, 0xff, 
0xff, 0xff, 0xf0, 0x1f, 0xf8, 0x0f, 0xff, 0xff, 
0xff, 0xff, 0xe0, 0xff, 0xff, 0x07, 0xff, 0xff, 
0xff, 0xff, 0xc3, 0xff, 0xff, 0xc3, 0xff, 0xff, 
0xff, 0xff, 0x87, 0xff, 0xff, 0xe1, 0xff, 0xff, 
0xff, 0xff, 0x0f, 0xff, 0xff, 0xf0, 0xff, 0xff, 
0xff, 0xfe, 0x1f, 0xff, 0xff, 0xf8, 0x7f, 0xff, 
0xff, 0xfc, 0x3f, 0xff, 0xff, 0xfc, 0x3f, 0xff, 
0xff, 0xfc, 0x7f, 0xff, 0xff, 0xfe, 0x3f, 0xff, 
0xff, 0xf8, 0xff, 0xff, 0xff, 0xff, 0x1f, 0xff, 
0xff, 0xf8, 0xff, 0xff, 0xff, 0xff, 0x1f, 0xff, 
0xff, 0xf1, 0xff, 0xff, 0xdf, 0xff, 0x8f, 0xff, 
0xff, 0xf1, 0xfe, 0x00, 0x00, 0x7f, 0x8f, 0xff, 
0xff, 0xf3, 0xf0, 0x00, 0x00, 0x0f, 0xc7, 0xff, 
0xff, 0xe3, 0xc0, 0x3f, 0xfc, 0x03, 0xc7, 0xff, 
0xff, 0xe3, 0x03, 0xff, 0xff, 0xc0, 0xc7, 0xff, 
0xff, 0xe2, 0x0f, 0xff, 0xff, 0xf0, 0x47, 0xff, 
0xff, 0xe0, 0x3f, 0x80, 0x01, 0xfc, 0x07, 0xff, 
0xff, 0xe0, 0x7c, 0x00, 0x00, 0x3e, 0x07, 0xff, 
0xff, 0xe0, 0xf0, 0x03, 0xf0, 0x0f, 0x07, 0xff, 
0xff, 0xe0, 0xe0, 0xff, 0xff, 0x07, 0x07, 0xff, 
0xff, 0xe0, 0xe3, 0xff, 0xff, 0xc7, 0x07, 0xff, 
0xff, 0xe0, 0xe7, 0xff, 0xff, 0xff, 0x07, 0xff, 
0xff, 0xe0, 0xe7, 0xff, 0xff, 0xff, 0x07, 0xff, 
0xff, 0xe0, 0xe7, 0xff, 0xff, 0xff, 0x07, 0xff, 
0xff, 0xe0, 0xe7, 0xff, 0xff, 0xff, 0x07, 0xff, 
0xff, 0xe0, 0xe7, 0xff, 0xff, 0xff, 0x07, 0xff, 
0xff, 0xe0, 0xe7, 0xff, 0xff, 0xfc, 0x07, 0xff, 
0xff, 0xe0, 0xe7, 0xff, 0xff, 0xf0, 0x07, 0xff, 
0xff, 0xe0, 0xe7, 0xff, 0xff, 0xc0, 0x07, 0xff, 
0xff, 0xe0, 0x7f, 0xfe, 0x0f, 0x02, 0x07, 0xff, 
0xff, 0xe0, 0x3f, 0xfc, 0x00, 0x0c, 0x07, 0xff, 
0xff, 0xe2, 0x1f, 0xf8, 0x00, 0x38, 0x47, 0xff, 
0xff, 0xf3, 0x07, 0xfc, 0x01, 0xe0, 0xcf, 0xff, 
0xff, 0xf1, 0x80, 0x7c, 0x0e, 0x01, 0x8f, 0xff, 
0xff, 0xf1, 0xe0, 0x00, 0x00, 0x07, 0x8f, 0xff, 
0xff, 0xf8, 0xfc, 0x00, 0x00, 0x3f, 0x1f, 0xff, 
0xff, 0xf8, 0xff, 0xc0, 0x03, 0xff, 0x1f, 0xff, 
0xff, 0xfc, 0x7f, 0xff, 0xff, 0xfe, 0x3f, 0xff, 
0xff, 0xf8, 0x3f, 0xff, 0xff, 0xfc, 0x1f, 0xff, 
0xff, 0xf0, 0x1f, 0xff, 0xff, 0xf8, 0x0f, 0xff, 
0xff, 0xf1, 0x0f, 0xff, 0xff, 0xf0, 0x8f, 0xff, 
0xff, 0xe3, 0x87, 0xff, 0xff, 0xe1, 0xc7, 0xff, 
0xff, 0xc3, 0xc1, 0xff, 0xff, 0x83, 0xc1, 0xff, 
0xfe, 0x01, 0xe0, 0x7f, 0xfe, 0x07, 0x80, 0x7f, 
0xf8, 0x10, 0xf8, 0x0f, 0xf0, 0x1f, 0x10, 0x1f, 
0xf0, 0x7c, 0x3e, 0x00, 0x00, 0x7c, 0x3e, 0x0f, 
0xe1, 0xfe, 0x1f, 0x80, 0x01, 0xf8, 0x7f, 0x87, 
0xe3, 0xff, 0x07, 0xff, 0x3f, 0xe0, 0xff, 0xc3, 
0xc7, 0xff, 0x81, 0xff, 0xff, 0x81, 0xff, 0xe3, 
0xc7, 0xff, 0xe0, 0x3f, 0xfc, 0x07, 0xff, 0xe3, 
0xc7, 0xff, 0xf8, 0x00, 0x00, 0x1f, 0xff, 0xf3, 
0xcf, 0xff, 0xfe, 0x00, 0x00, 0x7f, 0xff, 0xf3, 
0x8f, 0xff, 0xff, 0xe0, 0x07, 0xff, 0xff, 0xf1, 
0x8f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf1, 
0x8f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf1, 
0x8f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf9, 
0x9f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf9, 
0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// draw the ball at the current location
void drawBall(byte x, byte y) {
    tv.draw_rect(x, y, BALL_SIZE, BALL_SIZE, WHITE); 
}

// erases the ball at the current location
//  call this, then update the ball location, then call drawBall()
void eraseBall(byte x, byte y) {
    tv.draw_rect(x, y, BALL_SIZE, BALL_SIZE, BLACK);
}

// draw the vortex;
void drawVortex(byte x, byte y) {
    tv.draw_circle(x, y, VORTEX_SIZE, WHITE, WHITE);
}

// flash the vortex
void flashVortex(byte x, byte y) {
    
    tv.draw_circle(x, y, VORTEX_SIZE, WHITE, WHITE);
    delay(10);
    tv.draw_circle(x, y, VORTEX_SIZE, WHITE, BLACK);
    delay(10);
    tv.draw_circle(x, y, VORTEX_SIZE, WHITE, WHITE);
    delay(10);
    tv.draw_circle(x, y, VORTEX_SIZE, WHITE, BLACK);
    delay(10);
    tv.draw_circle(x, y, VORTEX_SIZE, WHITE, WHITE);
    
}

// prints the time left in seconds (3 chars) in the top banner
void updateTimer(int timeLeft) {
    
    char buffer[4];
    sprintf (buffer, "%03d", timeLeft); 
    tv.select_font(font6x8);
    tv.print(54, 2, buffer);
    
}

// updates the score; pass player # (1 or 2) and the score
void updateScore(byte player, int score) {

    char buffer[4];
    sprintf (buffer, "%03d", score); 
    tv.select_font(font6x8);

    if (player == 1) {
        tv.print(25, 2, buffer);
    }
    
    if (player == 2) {
        tv.print(109, 2, buffer);
    }

}

// draw the Astronaut
void drawAstronaut() {
    tv.bitmap(31, 14, astronaut);
}

// draw the paddles
void drawPaddles(byte player1Location, byte player2Location) {

    // player 1
    tv.draw_rect(2, player1Location, PADDLE_WIDTH, PADDLE_HEIGHT, WHITE, WHITE); 

    // player 2
    tv.draw_rect(125-PADDLE_WIDTH, player2Location, PADDLE_WIDTH, PADDLE_HEIGHT, WHITE, WHITE); 

}

// erase the paddles
void erasePaddles(byte player1Location, byte player2Location) {

    // player 1
    tv.draw_rect(2, player1Location, PADDLE_WIDTH, PADDLE_HEIGHT, BLACK, BLACK); 

    // player 2
    tv.draw_rect(125-PADDLE_WIDTH, player2Location, PADDLE_WIDTH, PADDLE_HEIGHT, BLACK, BLACK); 

}

