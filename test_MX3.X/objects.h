/* 
 * File:   game.h
 * Author: minht
 *
 * Created on December 1, 2022, 1:22 PM
 */

#ifndef GAME_H
#define	GAME_H
#define MAX_SIZE 16
/*
 * Elements within the game and their attributes
 * 1. Bird
 *      A. Position
 *      B. In Collision
 *      C. State
 * 2. Obstacle
 *      A. Track
 * 3. LCD Display
 *      A. LCD Array
 *      B. LCD index
 *      C. Button
 *          I. isPressed
 */



typedef struct Bird{
    enum {BOTTOM, TOP} birdPosition;
    enum {ALIVE, DEAD} birdState;
    enum {FALSE, TRUE} birdCollision;
    char birdStateAlive;
    char birdStateDead;
} Bird;

typedef struct Obstacle{
    /*
     Possible track combination
     * track1 / track1 shifted
     * track1 / track2
     * track2 / track1
     * track2 / track2 shifted
     */
    char topTrack[MAX_SIZE - 1]; //Index 0 of LCDsize is occupied by birdState
    char bottomTrack[MAX_SIZE - 1];
    int trackIndex;
} Obstacle;

typedef struct LCD{
    char topLCD[MAX_SIZE];
    char bottomLCD[MAX_SIZE];
    int LCDindex;
    enum {buttonLow, buttonHigh} buttonPress; //BTNC
} LCD;

typedef struct gameSelf{
    Bird gameBird;
    Obstacle gameObstacle;
    LCD gameLCD;
} gameSelf;



#endif	/* GAME_H */

