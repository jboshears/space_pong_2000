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

// play theme
void playTitleTheme() {

//return; // todo

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
