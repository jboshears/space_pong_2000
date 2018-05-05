/* 

SPACE PONG 2000
 - April 2018 -
 
*/

#include <TVout.h>
#include <fontALL.h>
#include <elapsedMillis.h>
#include "astronaut.h"   // astronaut bitmap for opening screen

// ----------------------------------------------------------------
// defined values
// ----------------------------------------------------------------
// game length in seconds
#define GAME_LENGTH 180

// ball size in pixels
#define BALL_SIZE 1

// vortex size
#define VORTEX_SIZE 4

// ----------------------------------------------------------------
// variables
// ----------------------------------------------------------------
// instantiate tv object
TVout tv;

typedef struct {
    int paddlePin;
    int buttonPin;
    String initials;
    int score;
} Player;

Player player1;
Player player2;

typedef struct {
    int x;    // x coordinate
    int y;    // y coordinate
    int dx;   // direction on the X axis
    int dy;   // direction on the Y axis
} Sphere;

Sphere ball;
Sphere vortex;

int timeLeft;
elapsedMillis timeElapsed;
// ----------------------------------------------------------------

// setup method
void setup() {

    // initialize screen to NTSC 128w x 96h
    tv.begin(NTSC, 128, 96);

    // initialize the pins
    player2.paddlePin = 1;  // analog pin 1
    player2.buttonPin = 2;  // digital pin 2

    // set the button pins to INPUT_PULLUP mode
    pinMode(player1.buttonPin, INPUT_PULLUP);

    // DON'T CONNECT ANALOG PIN 5!! 
    //  it needs to float for random seed generation
    randomSeed(analogRead(5));
    
    // show the intro screen
    introScreen(); 

}

// main game loop
void loop() {

    // draw the vortex
    drawVortex();

    // update ball position
    eraseBall();
    moveBall();
    drawBall();

    // update game clock
    if (timeElapsed > 1000) {
        timeLeft--;
        if (timeLeft == -1) { timeLeft = 0; }
        updateTimer(timeLeft);
        timeElapsed = 0;
    }

    // 25ms delay
    delay(25); 

}

// intro screen; stay here and loop the theme music
//  until a controller button is pressed; then 
//  initialize the game state and return
void introScreen() {

    tv.clear_screen();
   
    // 15 character string; 6 pixels width per character
    // uses 90 pixels; to center @ 128 pixels wide start at 15
    tv.select_font(font6x8);
    tv.print(19,3,"SPACE PONG 2000");
    
    // approximately 127w X 66h for graphic starting at y 12
    //tv.draw_rect(0,12,127,66,WHITE);
    
    // astronaut bitmap
    tv.bitmap(31, 14, astronaut);

    // 33 character string; 4 pixels width per character
    // uses 90 pixels; to center @ 128 pixels wide start at 15
    tv.select_font(font4x6);
    tv.print(12,81,"developed by john boshears");
    tv.print(16,88,"scored by andrew hartman");
    
    // max rectangle screen can handle, for debugging purposes
    //tv.draw_rect(0,0,127,95,WHITE);
    
    // play the game melody
    playTitleTheme();
    
    // initialize the game!
    initializeGame();

}

// initialize or the game play variables
void initializeGame() {

    // clear the screen
    tv.clear_screen();
    
    // get the player names
    getPlayerNames();
   
    // pong field; down 10 pixels; then 127 wide by 85 high
    tv.draw_rect(0,10,127,85,WHITE,BLACK);
    
    tv.select_font(font4x6);
        
    //player 1 score
    tv.print(3,2,player1.initials.c_str());
    tv.print(15,2,":");
    updateScore(1,0);

    //player 3 score
    tv.print(95,2,player2.initials.c_str());
    tv.print(107,2,":");
    updateScore(2,0);

    timeLeft = GAME_LENGTH;
    updateTimer(timeLeft);

    // setup the vortex
    vortex.x = 64;
    vortex.y = 52;

    // initialize the ball location and direction
    resetBall();

    // draw the the vortex
    drawVortex();

}

// setup the game ball
void resetBall() {

    // center ball for now so it drops into the middle
    ball.x = 64;
    ball.y = 52;

    // give the ball an intial heading on the x axis
    //  should be 1 or -1
    ball.dx = 0;
    while (ball.dx == 0) {
        ball.dx = getRandomDirection();
    }

    ball.dy = getRandomDirection();
    ball.dy *= random(1,3);

    dropBall();
}

// get the player names
void getPlayerNames() {

    tv.select_font(font6x8);
    tv.print(7,8,"Player 1, initials?");
    tv.print(54,16,"AAA");
    player1.initials = "BOB";
    player1.score = 0;
    
    tv.print(7,32,"Player 2, initials?");
    tv.print(54,40,"BBB");
    player2.initials = "ANN";
    player2.score = 0;
    
    delay(1000);
    tv.clear_screen();
    // todo finish up here.
    
}

// calculate new ball location
void moveBall() {  

    // TODO paddle detection

    // TODO for now, bounce off the walls
    if (ball.y == 93 || ball.y == 11) {
        ball.dy *= -1;
        wallBounceSound();
    }

    // player 1 scored
    if (ball.x == 125) {
        player1.score++;
        updateScore(1, player1.score);
        scoreSound(1);
        checkForGameOver();
        resetBall();
    }

    // player 2 scored
    if (ball.x == 1) {
        player2.score++;
        updateScore(2, player2.score);
        scoreSound(2);
        checkForGameOver();
        resetBall();
    }
    
    // is the ball in the vortex?
    if ( (pow(vortex.x - ball.x, 2)  + pow(vortex.y - ball.y, 2)) <= pow(VORTEX_SIZE, 2) ) {
        
        // it is! ominous tone and flash
        vortexSound();
        flashVortex();

        // time increases in the vortex
        //  this seemed like a good idea; but the game timer went up faster than it counted down
        // updateTimer(timeLeft++);

        // mess with the ball headings and location
        // x can't be 0
        ball.dx = 0;
        while (ball.dx == 0) {
            ball.dx = getRandomDirection();
        }
    
        ball.dy = getRandomDirection();
        ball.dy *= random(1,3);
        
    }

    // update position
    ball.x += ball.dx;
    ball.y += ball.dy;

    // Keep the ball within the threshold of the playing field
    //  don't let x go above 125 or below 1
    //  don't let y go above 93 or below 11
    if (ball.x > 125) { ball.x = 125; }
    if (ball.x < 1)   { ball.x = 1; }
    if (ball.y > 93)  { ball.y = 93; }
    if (ball.y < 11)  { ball.y = 11; }

}

// check and handle game over
void checkForGameOver() {

    if (timeLeft == 0) {
        // todo
        introScreen();
    }
    
}



// drop the ball onto the field
void dropBall() {

    byte startingRadius = 25;

    for (byte radius = startingRadius; radius > 0; radius--) {
        tv.draw_circle(ball.x, ball.y, radius, WHITE, WHITE);
        delay(20);
        tv.draw_circle(ball.x, ball.y, radius, BLACK, BLACK);
    }
    
    // drop the ball randomly in the vortex so the trajectories differ
    ball.x = random(61,67);
    ball.y = random(49,55);

    
}





// flash the vortex
void flashVortex() {
    
    tv.draw_circle(vortex.x, vortex.y, VORTEX_SIZE, WHITE, WHITE);
    delay(20);
    tv.draw_circle(vortex.x, vortex.y, VORTEX_SIZE, WHITE, BLACK);
    delay(20);
    tv.draw_circle(vortex.x, vortex.y, VORTEX_SIZE, WHITE, WHITE);
    delay(20);
    tv.draw_circle(vortex.x, vortex.y, VORTEX_SIZE, WHITE, BLACK);
    delay(20);
    tv.draw_circle(vortex.x, vortex.y, VORTEX_SIZE, WHITE, WHITE);
    
}



