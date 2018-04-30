/* 

SPACE PONG 2000
 - April 2018 -
 
*/

#include <TVout.h>
#include <fontALL.h>
#include <Tone.h>
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

// ----------------------------------------------------------------
// variables
// ----------------------------------------------------------------
// instantiate tv object
TVout tv;

typedef struct {
    String initials;
    int score;
} Player;

Player player1;
Player player2;

typedef struct {
    byte x;    // x coordinate
    byte y;    // y coordinate
    byte dx;   // direction on the X axis
    byte dy;   // direction on the Y axis
} Ball;

Ball ball;
Ball vortex;

int timeLeft;

elapsedMillis timeElapsed;
// ----------------------------------------------------------------



// setup method
void setup() {

    // initialize screen to NTSC 128w x 96h
    tv.begin(NTSC, 128, 96);

    // randomize the seed; hopefully analog pin 0 is floating
    randomSeed(analogRead(0));
    
    // show the intro screen
    // TODO introScreen(); 
    initializeGame();

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

    ball.x = 64;
    ball.y = 52;

    while (ball.dx == 0) {
        ball.dx = getRandomDirection();
    }

    while (ball.dy == 0) {
        ball.dy = getRandomDirection();
    }

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
        bounceSound();
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
        ball.dx = getRandomDirection();
        ball.dy = getRandomDirection();
        
    }

    // update position
    ball.x += ball.dx;
    ball.y += ball.dy;

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

	 // notes in the melody:
	int melody[] = {
		NOTE_A5,
		NOTE_GS5,
		NOTE_FS5,
		NOTE_E5,
		NOTE_A5,
		NOTE_GS5,
		NOTE_FS5,
		NOTE_E5,
		NOTE_A5,
		NOTE_GS5,
		NOTE_A5,
		NOTE_AS5,
		NOTE_B5,
		NOTE_GS5,
		NOTE_FS5,
		NOTE_E5
	};

	// iterate over the notes of the melody:
	for (int thisNote = 0; thisNote < 16; thisNote++) {

		// to calculate the note duration, take one second 
		// divided by the note type.
		//e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
		int noteDuration = 1000/2;
		tv.tone(melody[thisNote], noteDuration);
		
		//pause for the note's duration plus 30 ms:   	
     	delay(noteDuration + 30);
    	
	}

}

// ball bounce on wall sound
void bounceSound() {
    tv.tone(NOTE_C4,20);
}

// vortexSound
void vortexSound() {
    tv.tone(NOTE_F3,100); 
}

// score sound
void scoreSound(byte player) {

    if (player == 1) {
        tv.tone(NOTE_A4,100);
        delay(100); 
        tv.tone(NOTE_B4,100);
        delay(100);
        tv.tone(NOTE_C4,100);
        delay(100);
        tv.tone(NOTE_D4,100);
        delay(100);
        tv.tone(NOTE_E4,100);
        delay(100);
    }
    else {
        tv.tone(NOTE_E4,100);
        delay(100); 
        tv.tone(NOTE_D4,100); 
        delay(100);
        tv.tone(NOTE_C4,100); 
        delay(100);
        tv.tone(NOTE_B4,100); 
        delay(100);
        tv.tone(NOTE_A4,100); 
        delay(100);
    }
   
}

// returns random direction; -1, 0, 1
byte getRandomDirection() {

    byte initialX = random(0, 3);
    byte direction;

    if (initialX == 0) {
        direction = -1;
    }
    else if (initialX == 1) {
        direction = 1;
    }
    else {
        direction = 0;
    }

    return direction;
    
}


