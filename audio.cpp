#include "audio.h"
#include <Arduino.h>
#include <TVout.h>

extern TVout tv;

// play theme
void playTitleTheme() {

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

    return;

    // drop these for brevity?

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
