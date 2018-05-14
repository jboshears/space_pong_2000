#include "audio.h"
#include <Arduino.h>
#include <TVout.h>
#include <Bounce.h>

extern TVout tv;
extern Bounce button1Bounce;
extern Bounce button2Bounce;

// play theme
void playTitleTheme() {

    // measure 1 repeats 4 times
    if (!playMeasure1()) { return; }
    if (!playMeasure1()) { return; }
    if (!playMeasure1()) { return; }
    if (!playMeasure1()) { return; }

    // then 5,6 twice
    if (!playMeasure5()) { return; }
    if (!playMeasure6()) { return; }
    if (!playMeasure5()) { return; }
    if (!playMeasure6()) { return; }

    // finally, measure 1 two more times
    if (!playMeasure1()) { return; }
    if (!playMeasure1()) { return; }
    
}

boolean playMeasure1() {

    int count = 6;
    
    float note[count] = {C4, REST, G4, G4, G4, F4};
    float duration[count] = {Q, E, S, S, Q, Q};
    
    for (int i = 0; i < count; i++) {
        
        tv.tone(note[i], duration[i]);
        delay(duration[i]+1);   
               
        // check for button press & exit if detected
        button1Bounce.update();
        button2Bounce.update();
        
        if (button1Bounce.fallingEdge() || button2Bounce.fallingEdge()) {
            return false;
        }
        
    }

    return true;
    
}

boolean playMeasure5() {

    int count = 8;
    
    float note[count] = {G4, E4, G4, E4, G4, E4, G4, E4};
    float duration[count] = {E, E, E, E, E, E, E, E};
    
    for (int i = 0; i < count; i++) {
        
        tv.tone(note[i], duration[i]);
        delay(duration[i]+1);   
               
        // check for button press & exit if detected
        button1Bounce.update();
        button2Bounce.update();
        
        if (button1Bounce.fallingEdge() || button2Bounce.fallingEdge()) {
            return false;
        }
        
    }

    return true;
    
}

boolean playMeasure6() {

    int count = 8;
    
    float note[count] = {F4, D4, F4, D4, F4, D4, F4, D4};
    float duration[count] = {E, E, E, E, E, E, E, E};
    
    for (int i = 0; i < count; i++) {
        
        tv.tone(note[i], duration[i]);
        delay(duration[i]+1);   
               
        // check for button press & exit if detected
        button1Bounce.update();
        button2Bounce.update();
        
        if (button1Bounce.fallingEdge() || button2Bounce.fallingEdge()) {
            return false;
        }
        
    }

    return true;
    
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
