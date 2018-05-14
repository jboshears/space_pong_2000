#include "audio.h"
#include <Arduino.h>
#include <TVout.h>

extern TVout tv;

// play theme
void playTitleTheme() {

    int count = 68;
    
    float note[count] = 
        {C4, REST, G4, G4, G4, F4,          // measure 1
         C4, REST, G4, G4, G4, F4,          // measure 2; repeat of measure 1
         C4, REST, G4, G4, G4, F4,          // measure 3; repeat of measure 1
         C4, REST, G4, G4, G4, F4,          // measure 4; repeat of measure 1
         G4, E4, G4, E4, G4, E4, G4, E4,    // measure 5
         F4, D4, F4, D4, F4, D4, F4, D4,    // measure 6
         G4, E4, G4, E4, G4, E4, G4, E4,    // measure 7; repeat of measure 5
         F4, D4, F4, D4, F4, D4, F4, D4,    // measure 8; repeat of measure 6
         C4, REST, G4, G4, G4, F4,          // measure 9; repeat of measure 1
         C4, REST, G4, G4, G4, F4};         // measure 10; repeat of measure 1
         
    float duration[count] = 
        {Q, E, S, S, Q, Q,          // measure 1
         Q, E, S, S, Q, Q,          // measure 2; repeat of measure 1
         Q, E, S, S, Q, Q,          // measure 3; repeat of measure 1
         Q, E, S, S, Q, Q,          // measure 4; repeat of measure 1
         E, E, E, E, E, E, E, E,    // measure 5
         E, E, E, E, E, E, E, E,    // measure 6
         E, E, E, E, E, E, E, E,    // measure 7; repeat of measure 5
         E, E, E, E, E, E, E, E,    // measure 8; repeat of measure 6
         Q, E, S, S, Q, Q,          // measure 9; repeat of measure 1
         Q, E, S, S, Q, Q};         // measure 10; repeat of measure 1
         
    for (int i = 0; i < count; i++) {
        tv.tone(note[i], duration[i]);
        delay(duration[i]+1);   
        // TODO; check for button press & exit if detected
    }

}

// end of game theme
void endGameTheme() {

    int count = 16;
    float note[count] = {G4, E4, G4, E4, G4, E4, G4, E4, F4, D4, F4, D4, F4, D4, F4, D4};
    float duration[count] = {E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E};

    for (int i = 0; i < count; i++) {
        tv.tone(note[i], duration[i]);
        delay(duration[i]+1);   
    }

}

// TODO: new high score melody
void newHighScoreMelody() {

    // TODO
    
}

// ball bounce on wall sound
void wallBounceSound() {   
    tv.tone(E4,20);  
}

// ball bounce on paddle sound
void paddleBounceSound() {   
    tv.tone(Gb4,20);
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
