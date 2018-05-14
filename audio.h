#include <avr/pgmspace.h>
#include <Arduino.h>
#ifndef AUDIO
#define AUDIO

// musical notes and durations
#define REST 0
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

// function definitions
void playTitleTheme();
void endGameTheme();
void newHighScoreMelody();
void wallBounceSound();
void paddleBounceSound();
void vortexSound();
void scoreSound(byte player);

#endif
