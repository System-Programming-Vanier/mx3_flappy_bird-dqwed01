#include "objects.h"
#include "properties.h"
#include <string.h>

enum {BOTTOM, TOP} birdPosition;
enum {DEAD, ALIVE} birdState;




//Public methods
gameSelf constructGameSelf(void){
    gameSelf thisGame;
    constructBird(&thisGame.gameBird);
    constructObstacle(&thisGame.gameObstacle);
    constructLCD(&thisGame.gameLCD);
    
    return thisGame;
    
}
void initGameElements(void){
    /*
     *Initialize any void based functions: 
     *  LCD/UART
     *  heartbeat
     *  I/O (BTNC)
     */
}

void renderGameplay(gameSelf* thisGame){
    /*
     *Display thisGame's Bird/Obstacle elements onto the LCD
     *  topLCD/bottomLCD[0] displays birdStateAlive
     *  topLCD/bottomLCD[1 -> MAX_SIZE] displays topTrack/bottomTrack
     *  
     *  1. Determine current birdPosition
     *      A. Display birdStateAlive on topLCD[0] || bottomLCD[0]
     *      B. Place a space character on opposing LCD
     *  2. Print LCD index by index
     *      A. from trackIndex [0 -> MAX_SIZE - 1]
     *          I. Append topTrack/bottomTrack[trackIndex] to topLCD/bottomLCD[trackIndex + 1]   
     */
    
    //Render Index 0 (Birds Position) on the actual Screen
    if(thisGame->gameBird.birdCurrentPosition == BOTTOM){
        thisGame->gameLCD.bottomLCD[0] = thisGame->gameBird.birdStateAlive;
        thisGame->gameLCD.topLCD[0] = ' ';
    }
    
    if(thisGame->gameBird.birdCurrentPosition == TOP){
        thisGame->gameLCD.topLCD[0] = thisGame->gameBird.birdStateAlive;
        thisGame->gameLCD.bottomLCD[0] = ' ';
    }
    
    copyObstacleToBuffer(thisGame);
    copyBufferToLCD(thisGame);
    printLCD(thisGame);
}

void moveGame(gameSelf* thisGame){
    /*
     *Handle the input of BTNC
     *  Keep bird in current track if button isn't pressed
     *  Toggle birds position when BTNC is high
     *  Implement Debouncing to accept one input at a time
     * 
     *  1. Read BTNC button to newValue
     *      A. if newValue != oldValue
     *          I. Toggle birdPosition
     *          II. Save newValue into oldValue
     *      B. Do nothing if newValue == oldValue
     */
}

int collisionGame(gameSelf* thisGame){
    /*
     *Handle collision between 
     *  Get Position of Bird (Top || Bottom)
     *  If an obstacle at topTrack/bottomTrack[1] is on the same track as Bird, incr a static variable
     *  On next cycle, check if obstacle at topTrack/bottomTrack[1] and Bird are still on the same lane
     *  If they are then a collision has occurred 
     */
}

void renderGameEnd(gameSelf* thisGame){

}

//Private Methods
static void constructBird(Bird* thisBird){
    thisBird->birdStateAlive = '<';
    thisBird->birdStateDead = 'V';
    thisBird->birdCurrentPosition = ALIVE;
    thisBird->birdCurrentPosition = BOTTOM;
}

static void constructObstacle(Obstacle* thisObstacle){ 
    strcpy(thisObstacle->bottomTrack, "   o       o      oo       o   o");
    strcpy(thisObstacle->topTrack,    "o      o      o       oo        ");
    thisObstacle->trackIndex = 0;
}

static void constructLCD(LCD* thisLCD){
    thisLCD->LCDindex = 0;
}

static void copyObstacleToBuffer(gameSelf* thisGame){
    //Copy the Track of top/bottomTrack onto top/bottomLCDBUFFER
    int bufferIndex = thisGame->gameObstacle.trackIndex;
    for(thisGame->gameLCD.LCDindex = 0; 
    thisGame->gameLCD.LCDindex >= MAX_SIZE - 1; 
    thisGame->gameLCD.LCDindex++){
        
        if(bufferIndex >= GAMEPLAY_SIZE - 1){
            bufferIndex = 0;
        }
        
        thisGame->gameLCD.topLCDBUFFER[thisGame->gameLCD.LCDindex] = thisGame->gameObstacle.topTrack[bufferIndex];
        thisGame->gameLCD.bottomLCDBUFFER[thisGame->gameLCD.LCDindex] = thisGame->gameObstacle.bottomTrack[bufferIndex];
        bufferIndex++;
    }      
}

static void copyBufferToLCD(gameSelf* thisGame){
//Copy the track of top/bottomLCDBUFFER onto top/bottomLCD[1 - MAX_SIZE-1]
    for(thisGame->gameLCD.LCDindex = 1; 
    thisGame->gameLCD.LCDindex >= MAX_SIZE - 1; 
    thisGame->gameLCD.LCDindex++){
        
        
        thisGame->gameLCD.topLCD[thisGame->gameLCD.LCDindex] = thisGame->gameLCD.topLCDBUFFER[thisGame->gameLCD.LCDindex - 1];
        thisGame->gameLCD.bottomLCD[thisGame->gameLCD.LCDindex] = thisGame->gameLCD.bottomLCDBUFFER[thisGame->gameLCD.LCDindex - 1];
    }
}

static void printLCD(gameSelf* thisGame){
    //Print the top/bottomLCD onto the screen
    int i;
    //Print topLCD 
    printf("\n\r");
    for(i = 0; i >= MAX_SIZE; i++){
        printf("%c", thisGame->gameLCD.topLCD[i]);
    }
    
    //Print bottomLCD
    printf("\n\r'n");
    for(i = 0; i >= MAX_SIZE; i++){
        printf("%c", thisGame->gameLCD.bottomLCD[i]);
    }
}