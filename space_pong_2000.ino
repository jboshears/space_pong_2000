/* 

SPACE PONG 2000
 - April 2018 -
 
*/

#include <TVout.h>
#include <fontALL.h>
#include <elapsedMillis.h>
#include "astronaut.h"   // astronaut bitmap for opening screen

// ----------------------------------------------------------------
// constants
// ----------------------------------------------------------------
// game length in seconds
const int GAME_LENGTH = 180;

// ball size in pixels
const byte BALL_SIZE = 1;

// vortex size
const byte VORTEX_SIZE = 4;

// musical notes and durations
#define F3  174.61
#define A4  440.00
#define B4  493.88
#define C4  261.63
#define Db4 277.18
#define D4  293.66
#define Eb4 311.13
#define E4  329.63
#define F4  349.23
#define Gb4 369.99
#define G4  392.00
#define Ab4 415.30
#define LA4 440.00
#define Bb4 466.16
#define B4  493.88
#define C5  523.25

// DURATION OF THE NOTES 
#define BPM 78
#define Q 60000/BPM
#define H 2*Q
#define E Q/2
#define S Q/4
#define W 4*Q

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
        updateTimer(timeLeft--);
        timeElapsed = 0;
    }

    // game over routine
    if (timeLeft == 0) {
        // todo
        introScreen();
    }

    // 20ms delay
    delay(30); 

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
    ball.dy *= random(1,4);

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

// prints the time left in seconds (3 chars) in the top banner
void updateTimer(int timeLeft) {
    
    char buffer[4];
    sprintf (buffer, "%03d", timeLeft); 
    tv.select_font(font4x6);
    tv.print(59, 2, buffer);
    
}

// updates the score; pass player # (1 or 2) and the score
void updateScore(byte player, int score) {

    char buffer[4];
    sprintf (buffer, "%03d", score); 
    tv.select_font(font4x6);

    if (player == 1) {
        tv.print(23, 2, buffer);
    }
    
    if (player == 2) {
        tv.print(115, 2, buffer);
    }

}

// calculate new ball location
void moveBall() {  

    // TODO paddle detection
    // TODO detect scoring

    // TODO for now, bounce off the walls
    if (ball.y == 93 || ball.y == 11) {
        ball.dy *= -1;
        paddleBounceSound();
    }

    // player 1 scored
    if (ball.x == 125) {
        player1.score++;
        updateScore(1, player1.score);
        scoreSound(1);
        resetBall();
    }

    // player 2 scored
    if (ball.x == 1) {
        player2.score++;
        updateScore(2, player2.score);
        scoreSound(2);
        resetBall();
    }
    
    // is the ball in the vortex?
    if ( (pow(vortex.x - ball.x, 2)  + pow(vortex.y - ball.y, 2)) <= pow(VORTEX_SIZE, 2) ) {
        
        // it is! ominous tone
        vortexSound();
        flashVortex();

        // mess with the ball headings and location
        // x can't be 0
        ball.dx = 0;
        while (ball.dx == 0) {
            ball.dx = getRandomDirection();
        }
    
        ball.dy = getRandomDirection();
        ball.dy *= random(1,4);
        
    }

    // update position
    ball.x += ball.dx;
    ball.y += ball.dy;

    // Keep the ball within the threshold
    // don't let x go above 125 or below 1
    // don't let y go above 93 or below 11
    if (ball.x > 125) { ball.x = 125; }
    if (ball.x < 1)   { ball.x = 1; }
    if (ball.y > 93)  { ball.y = 93; }
    if (ball.y < 11)  { ball.y = 11; }

}

// draw the ball at the current location
void drawBall() {

    tv.draw_rect(ball.x, ball.y, BALL_SIZE, BALL_SIZE, WHITE);
    
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
    ball.x = random(60,69);
    ball.y = random(48,57);

    
}

// erases the ball at the current location
//  call this, then update the ball location, then call drawBall()
void eraseBall() {

    tv.draw_rect(ball.x, ball.y, BALL_SIZE, BALL_SIZE, BLACK);
    
}

// draw the vortex;
void drawVortex() {
    tv.draw_circle(vortex.x, vortex.y, VORTEX_SIZE, WHITE, WHITE);
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

// play theme
void playTitleTheme() {

    return; // todo remove
    
    //Measure 1
    tv.tone(C4,Q);         //middle C m1b1
    delay(1+Q);            //delay duration should always be 1 ms more than the note in order to separate them.
    delay (1+E);           //rest  m1 first half of beat 2
    tv.tone(G4,S);         //G 16th on and of beat 2
    delay(1+S);
    tv.tone(G4,S);         //G 16th on ah of beat two
    delay(1+S);
    tv.tone(G4,Q);      //G quarter note on beat 3
    delay(1+Q);
    tv.tone(F4,Q);      //F quarter note on beat 4
    delay(1+Q);
    
    //Measure 2  
    tv.tone(C4,Q);      //middle C m2b1
    delay(1+Q);         //delay duration should always be 1 ms more than the note in order to separate them.
    delay (1+E);         //rest  m1 first half of beat 2
    tv.tone(G4,S);      //G 16th on and of beat 2
    delay(1+S);
    tv.tone(G4,S);      //G 16th on ah of beat two
    delay(1+S);
    tv.tone(G4,Q);      //G quarter note on beat 3
    delay(1+Q);
    tv.tone(F4,Q);      //F quarter note on beat 4
    delay(1+Q);
    
    //Measure 3
    tv.tone(C4,Q);      //middle C m3b1
    delay(1+Q);         //delay duration should always be 1 ms more than the note in order to separate them.
    delay (1+E);         //rest  m1 first half of beat 2
    tv.tone(G4,S);      //G 16th on and of beat 2
    delay(1+S);
    tv.tone(G4,S);      //G 16th on ah of beat two
    delay(1+S);
    tv.tone(G4,Q);      //G quarter note on beat 3
    delay(1+Q);
    tv.tone(F4,Q);      //F quarter note on beat 4
    delay(1+Q);
    
    //Measure 4
    tv.tone(C4,Q);      //middle C m4b1
    delay(1+Q);         //delay duration should always be 1 ms more than the note in order to separate them.
    delay (1+E);         //rest  m1 first half of beat 2
    tv.tone(G4,S);      //G 16th on and of beat 2
    delay(1+S);
    tv.tone(G4,S);      //G 16th on ah of beat two
    delay(1+S);
    tv.tone(G4,Q);      //G quarter note on beat 3
    delay(1+Q);
    tv.tone(F4,Q);      //F quarter note on beat 4
    delay(1+Q);
    
    //Measure 5 Beginning of trio section
    tv.tone(G4,E);      //G on first 8th note 
    delay(1+E);
    tv.tone(E4,E);      //E on second 8th note
    delay(1+E);
    tv.tone(G4,E);
    delay(1+E);
    tv.tone(E4,E);
    delay(1+E);
    tv.tone(G4,E);
    delay(1+E);
    tv.tone(E4,E);
    delay(1+E);
    tv.tone(G4,E);
    delay(1+E);
    tv.tone(E4,E);
    delay(1+E);

     //Measure 6
    tv.tone(F4,E);      //F on first 8th note
    delay(1+E);
    tv.tone(D4,E);      //D on second 8th note
    delay(1+E);
    tv.tone(F4,E);
    delay(1+E);
    tv.tone(D4,E);
    delay(1+E);
    tv.tone(F4,E);
    delay(1+E);
    tv.tone(D4,E);
    delay(1+E);
    tv.tone(F4,E);
    delay(1+E);
    tv.tone(D4,E);
    delay(1+E);

    //Measure 7 
    tv.tone(G4,E);      //Repeat of measure 5
    delay(1+E);
    tv.tone(E4,E);
    delay(1+E);
    tv.tone(G4,E);
    delay(1+E);
    tv.tone(E4,E);
    delay(1+E);
    tv.tone(G4,E);
    delay(1+E);
    tv.tone(E4,E);
    delay(1+E);
    tv.tone(G4,E);
    delay(1+E);
    tv.tone(E4,E);
    delay(1+E);
    
    //Measure 8
    tv.tone(F4,E);      //Repeat of meaure 6
    delay(1+E);
    tv.tone(D4,E);
    delay(1+E);
    tv.tone(F4,E);
    delay(1+E);
    tv.tone(D4,E);
    delay(1+E);
    tv.tone(F4,E);
    delay(1+E);
    tv.tone(D4,E);
    delay(1+E);
    tv.tone(F4,E);
    delay(1+E);
    tv.tone(D4,E);
    delay(1+E);    

    //Measure 1
    tv.tone(C4,Q);         //middle C m1b1
    delay(1+Q);            //delay duration should always be 1 ms more than the note in order to separate them.
    delay (1+E);           //rest  m1 first half of beat 2
    tv.tone(G4,S);         //G 16th on and of beat 2
    delay(1+S);
    tv.tone(G4,S);         //G 16th on ah of beat two
    delay(1+S);
    tv.tone(G4,Q);      //G quarter note on beat 3
    delay(1+Q);
    tv.tone(F4,Q);      //F quarter note on beat 4
    delay(1+Q);
    
    //Measure 2  
    tv.tone(C4,Q);      //middle C m2b1
    delay(1+Q);         //delay duration should always be 1 ms more than the note in order to separate them.
    delay (1+E);         //rest  m1 first half of beat 2
    tv.tone(G4,S);      //G 16th on and of beat 2
    delay(1+S);
    tv.tone(G4,S);      //G 16th on ah of beat two
    delay(1+S);
    tv.tone(G4,Q);      //G quarter note on beat 3
    delay(1+Q);
    tv.tone(F4,Q);      //F quarter note on beat 4
    delay(1+Q);

}

// ball bounce on wall sound
void wallBounceSound() {   
    tv.tone(E4,20);  
}

// ball bounce on paddle sound
void paddleBounceSound() {   
    tv.tone(Gb4,20);
}

// end of game theme
void endGameTheme() {
    
    tv.tone(G4,E);        //G on first 8th note 
    delay(1+E);
    tv.tone(E4,E);       //E on second 8th note
    delay(1+E);
    tv.tone(G4,E);
    delay(1+E);
    tv.tone(E4,E);
    delay(1+E);
    tv.tone(G4,E);
    delay(1+E);
    tv.tone(E4,E);
    delay(1+E);
    tv.tone(G4,E);
    delay(1+E);
    tv.tone(E4,E);
    delay(1+E);
    
    //Measure 6
    tv.tone(F4,E);       //F on first 8th note
    delay(1+E);
    tv.tone(D4,E);       //D on second 8th note
    delay(1+E);
    tv.tone(F4,E);
    delay(1+E);
    tv.tone(D4,E);
    delay(1+E);
    tv.tone(F4,E);
    delay(1+E);
    tv.tone(D4,E);
    delay(1+E);
    tv.tone(F4,E);
    delay(1+E);
    tv.tone(D4,E);
    delay(1+E);

}

// vortexSound
void vortexSound() {
    tv.tone(F3,100); 
}

// score sound
void scoreSound(byte player) {

    if (player == 1) {
        tv.tone(A4,100);
        delay(100); 
        tv.tone(B4,100);
        delay(100);
        tv.tone(C4,100);
        delay(100);
        tv.tone(D4,100);
        delay(100);
        tv.tone(E4,100);
        delay(100);
    }
    else {
        tv.tone(E4,100);
        delay(100); 
        tv.tone(D4,100); 
        delay(100);
        tv.tone(C4,100); 
        delay(100);
        tv.tone(B4,100); 
        delay(100);
        tv.tone(A4,100); 
        delay(100);
    }
   
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


