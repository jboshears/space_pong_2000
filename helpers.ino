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

// draw the ball at the current location
void drawBall() {
    tv.draw_rect(ball.x, ball.y, BALL_SIZE, BALL_SIZE, WHITE); 
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
