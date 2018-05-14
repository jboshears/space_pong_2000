/* 

SPACE PONG 2000
 - April 2018 -
 
*/

#include <TVout.h>
#include <fontALL.h>
#include <elapsedMillis.h>
#include <Bounce.h>
#include "graphics.h"   // graphics library
#include "audio.h"      // sound library

// ----------------------------------------------------------------
// defined values
// ----------------------------------------------------------------
// game length in seconds
#define GAME_LENGTH 180

#define PLAYER1_BTN 4
#define PLAYER2_BTN 2
#define PLAYER1_POT 5
#define PLAYER2_POT 1

// ----------------------------------------------------------------
// variables
// ----------------------------------------------------------------
// instantiate tv object
TVout tv;

typedef struct {
    int  paddleLocation;
    int  oldPaddleLocation;
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

Bounce button1Bounce = Bounce(PLAYER1_BTN, 100);
Bounce button2Bounce = Bounce(PLAYER2_BTN, 100);

Sphere ball;
Sphere vortex;

int timeLeft;
elapsedMillis timeElapsed;
// ----------------------------------------------------------------

// setup method
void setup() {

    // initialize screen to NTSC 128w x 96h
    tv.begin(NTSC, 128, 96);
   
    // DON'T CONNECT ANALOG PIN 5!! 
    //  it needs to float for random seed generation
    randomSeed(analogRead(5));

    // set the button pins to INPUT_PULLUP mode
    pinMode(PLAYER1_BTN, INPUT_PULLUP);
    pinMode(PLAYER2_BTN, INPUT_PULLUP);
    
    // show the intro screen
    introScreen(); 

}

// main game loop
void loop() {

    // draw the vortex
    drawVortex(vortex.x, vortex.y);

    // erase paddles, get the location, and redraw them
    erasePaddles(player1.paddleLocation, player2.paddleLocation);
    
    player1.paddleLocation = map(analogRead(PLAYER1_POT), 515, 1023, 11, 94 - PADDLE_HEIGHT);
    player2.paddleLocation = map(analogRead(PLAYER2_POT), 515, 1023, 11, 94 - PADDLE_HEIGHT); 
    
    // don't let the paddle location go below 11
    if (player1.paddleLocation < 11) { player1.paddleLocation = 11; }
    if (player2.paddleLocation < 11) { player2.paddleLocation = 11; }
    
    drawPaddles(player1.paddleLocation, player2.paddleLocation);

    // update ball position
    eraseBall(ball.x, ball.y);
    moveBall();
    drawBall(ball.x, ball.y);

    // update game clock
    if (timeElapsed > 1000) {
        timeLeft--;
        if (timeLeft < 0) { timeLeft = 0; }
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
    drawAstronaut();

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
    
    tv.select_font(font6x8);
        
    //player 1 score
    tv.print(1,2,player1.initials.c_str());
    tv.print(19,2,":");
    updateScore(1,0);

    //player 3 score
    tv.print(85,2,player2.initials.c_str());
    tv.print(103,2,":");
    updateScore(2,0);

    timeLeft = GAME_LENGTH;
    updateTimer(timeLeft);

    // setup the vortex
    vortex.x = 64;
    vortex.y = 52;

    // draw the the vortex
    drawVortex(vortex.x, vortex.y);

    // initialize the paddles
    player1.paddleLocation = map(analogRead(PLAYER1_POT), 535, 1023, 11, 94 - PADDLE_HEIGHT);
    player2.paddleLocation = map(analogRead(PLAYER2_POT), 535, 1023, 11, 94 - PADDLE_HEIGHT);
    player1.oldPaddleLocation = player1.paddleLocation;
    player2.oldPaddleLocation = player2.paddleLocation;
    drawPaddles(player1.paddleLocation, player2.paddleLocation);

    // initialize the ball location and direction
    resetBall();


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

char getLetterFromPot(byte pot, Bounce *bounceObject, byte x, byte y) {

    byte cursorColor = WHITE;
    byte lowerAsciiRange = 65; // 65 is A
    byte upperAsciiRange = 91; // 90 is Z
    
    while (true) {
        
        tv.draw_line(x, y+8, x+6, y+8, cursorColor);
        
        if (cursorColor == WHITE) { 
            cursorColor = BLACK;
        }
        else {
            cursorColor = WHITE;
        }

        char c = constrain(map(analogRead(pot), 515, 1023, lowerAsciiRange, upperAsciiRange), lowerAsciiRange, upperAsciiRange);

        // translate 91 to 32 (space)
        if (c == 91) { c = 32; }
        
        tv.print(x,y,c);
        
        bounceObject->update();
        if (bounceObject->fallingEdge()) {
            tv.draw_line(x, y+8, x+6, y+8, BLACK);
            return c;
        }
        
        delay(250);
        
    }   
    
}

// get the player names
void getPlayerNames() {

    tv.select_font(font6x8);

    // player 1:
    player1.initials = "";
    player1.score = 0;
    tv.print(7,8,"Player 1?");
    tv.print(54,16,"AAA");

    // get initials from pot
    player1.initials += getLetterFromPot(PLAYER1_POT, &button1Bounce, 54, 16);
    player1.initials += getLetterFromPot(PLAYER1_POT, &button1Bounce, 60, 16);
    player1.initials += getLetterFromPot(PLAYER1_POT, &button1Bounce, 66, 16);

    // player 2:
    player2.initials = "";
    player2.score = 0;
    tv.print(7,32,"Player 2?");
    tv.print(54,40,"AAA");

     // get initials from pot
    player2.initials += getLetterFromPot(PLAYER2_POT, &button2Bounce, 54, 40);
    player2.initials += getLetterFromPot(PLAYER2_POT, &button2Bounce, 60, 40);
    player2.initials += getLetterFromPot(PLAYER2_POT, &button2Bounce, 66, 40);
    
    delay(1000);
    tv.clear_screen();
    
}

// calculate new ball location
void moveBall() {  

    // bounced off of paddle 1
    if ( ball.x == 5 && ball.y >= player1.paddleLocation && ball.y <= player1.paddleLocation + PADDLE_HEIGHT)  {
        paddleBounceSound();
        ball.dx *= -1; 
        ball.dy *= -1; 
        //ball.dy *= random(1,3);
    }

    // bounced off of paddle 2
    if ( ball.x == 121 && ball.y >= player2.paddleLocation && ball.y <= player2.paddleLocation + PADDLE_HEIGHT)  {
        paddleBounceSound();
        ball.dx *= -1; 
        ball.dy *= -1; 
        //ball.dy *= random(1,3);
    }

    // bounce off the walls
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
        flashVortex(vortex.x, vortex.y);

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
        
        delay(500);

        tv.clear_screen();
        tv.select_font(font8x8);
        tv.print(28, 30, "GAME OVER");
        
        char scoreBuffer1[4];
        sprintf (scoreBuffer1, "%03d", player1.score); 

        char scoreBuffer2[4];
        sprintf (scoreBuffer2, "%03d", player2.score); 
    
        if (player2.score > player1.score) {
        
            tv.print(36, 42, player2.initials.c_str());
            tv.print(68, 42, scoreBuffer2);
            tv.print(36, 52, player1.initials.c_str());
            tv.print(68, 52, scoreBuffer1);

            tv.print(24, 64, "WINNER");
            tv.print(80, 64, player2.initials.c_str());
          
        }
        
        else if (player1.score > player2.score) {

            tv.print(36, 42, player1.initials.c_str());
            tv.print(68, 42, scoreBuffer1);
            tv.print(36, 52, player2.initials.c_str());
            tv.print(68, 52, scoreBuffer2);

            tv.print(24, 64, "WINNER");
            tv.print(80, 64, player1.initials.c_str());
            
        }
        else {

            tv.print(36, 42, player1.initials.c_str());
            tv.print(68, 42, scoreBuffer1);
            tv.print(36, 52, player2.initials.c_str());
            tv.print(68, 52, scoreBuffer2);
            
        }
        
        endGameTheme();
        delay(4000); // todo wait for button press here
        introScreen();
        
    }
    
}

// drop the ball onto the field
void dropBall() {

    // pong field; down 10 pixels; then 127 wide by 85 high
    tv.draw_rect(0,10,127,85,WHITE,BLACK);
    drawPaddles(player1.paddleLocation, player2.paddleLocation);

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

// returns random direction; -1, 0, 1
int getRandomDirection() {

    int direction = random(1, 4);

    if (direction == 1) {
        return 1;
    }
    else if (direction == 2) {
        return -1;
    }
    else {
        return 0;
    }
    
}


