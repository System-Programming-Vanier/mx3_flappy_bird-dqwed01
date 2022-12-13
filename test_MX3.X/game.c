#include "objects.h"
#include "properties.h"
#include <xc.h>
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
    
    TRISFbits.TRISF4 = 1; //BTNC set as Input
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
    
    static int obstacleCounter = 0; //Move Obstacles every 250 ms
    
    //Handle Obstacle Movement
    if(obstacleCounter++ >= 12){ //SUPPOSE TO BE obstacleCounter++ >= 25 BUT CAUSES DELAY OF OVER A SECOND
        obstacleCounter = 0;
        if(thisGame->gameObstacle.trackIndex++ >= GAMEPLAY_SIZE - 1) thisGame->gameObstacle.trackIndex = 0;
    }
    
    //Handle BTNC bird
    if(handleBTNC() == 1){
        if (thisGame->gameBird.birdCurrentPosition == TOP)thisGame->gameBird.birdCurrentPosition = BOTTOM;
        else if (thisGame->gameBird.birdCurrentPosition == BOTTOM)thisGame->gameBird.birdCurrentPosition = TOP;
    }
}

int collisionGame(gameSelf* thisGame){
    /*
     *Handle collision between 
     *  Get Position of Bird (Top || Bottom)
     *  If an obstacle at topTrack/bottomTrack[1] is on the same track as Bird, incr a static variable
     *  On next cycle, check if obstacle at topTrack/bottomTrack[1] and Bird are still on the same lane
     *  If they are then a collision has occurred 
     */
    static int inCollision = 0;
    char birdPosition = thisGame->gameBird.birdCurrentPosition;
    char topObstacle = thisGame->gameLCD.topLCD[1];
    char bottomObstacle = thisGame->gameLCD.bottomLCD[1];
    
    switch(birdPosition){
        case BOTTOM:
            if(bottomObstacle == 'o') inCollision++;
            if(bottomObstacle == ' ') inCollision = 0;
            break;
        case TOP:
            if(topObstacle == 'o') inCollision++;
            if(topObstacle == ' ') inCollision = 0;
            break;        
    }
    
    if(inCollision == 10) return 0;
    else if(inCollision < 10) return 1;
}

void renderGameEnd(gameSelf* thisGame){
    //Toggle the state of Bird and print a still obstacle onto the LCD every 120ms
    static int birdCounter = 0;
    if (birdCounter++ == 12){
        birdCounter = 0;
        toggleBirdState(thisGame);    
        tone_high(10);
        tone_low(5);
        printLCD(thisGame);
    }
    
    
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
    thisGame->gameLCD.LCDindex <= MAX_SIZE - 1; 
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
    thisGame->gameLCD.LCDindex <= MAX_SIZE - 1; 
    thisGame->gameLCD.LCDindex++){
        
        
        thisGame->gameLCD.topLCD[thisGame->gameLCD.LCDindex] = thisGame->gameLCD.topLCDBUFFER[thisGame->gameLCD.LCDindex - 1];
        thisGame->gameLCD.bottomLCD[thisGame->gameLCD.LCDindex] = thisGame->gameLCD.bottomLCDBUFFER[thisGame->gameLCD.LCDindex - 1];
    }
}

static void printLCD(gameSelf* thisGame){
    //Print the top/bottomLCD onto the screen
    int i;
    //Erase both lines
    printf("\n\r                ");
    printf("\n\r\n                ");
    //Print topLCD 
    printf("\n\r");
    for(i = 0; i < MAX_SIZE; i++){
        printf("%c", thisGame->gameLCD.topLCD[i]);
    }
    
    //Print bottomLCD
    printf("\n\r\n");
    for(i = 0; i < MAX_SIZE; i++){
        printf("%c", thisGame->gameLCD.bottomLCD[i]);
    }
}

static int handleBTNC(void){
    /*
     * Read input from BTNC
     *  1. Implement Debounce function 
     *      A. If BTNC is High and oldValue is Low return 1
     *          I. Write High into oldValue
     *      B. If BTNC is High and oldValue is High return 0
     *          I. Don't write anything to oldValue
     *      C. If BTNC is Low (Don't care about oldValue) return 0
     *          I. Write Low into oldValue
     */
    
    static int oldValue = 0;
    int newValue = BTNC;
    
    if (newValue == oldValue) return 0;
    if (newValue != oldValue){
        oldValue = newValue;
        tone_high(5);
        tone_low(5);
        return newValue;

    } 
}

static void toggleBirdState(gameSelf* thisGame){
    //Flip the Bird from < to V and vice-cersa
    if(thisGame->gameBird.birdCurrentPosition == BOTTOM){
        if(thisGame->gameLCD.bottomLCD[0] == '<'){
            thisGame->gameLCD.bottomLCD[0] = thisGame->gameBird.birdStateDead;
            thisGame->gameLCD.topLCD[0] = ' ';
        }
        else if(thisGame->gameLCD.bottomLCD[0] == 'V'){
            thisGame->gameLCD.bottomLCD[0] = thisGame->gameBird.birdStateAlive;
            thisGame->gameLCD.topLCD[0] = ' ';
        }
    }
    
    if(thisGame->gameBird.birdCurrentPosition == TOP){
        if(thisGame->gameLCD.topLCD[0] == '<'){
            thisGame->gameLCD.topLCD[0] = thisGame->gameBird.birdStateDead;
            thisGame->gameLCD.bottomLCD[0] = ' ';
        }
        else if(thisGame->gameLCD.topLCD[0] == 'V'){
            thisGame->gameLCD.topLCD[0] = thisGame->gameBird.birdStateAlive;
            thisGame->gameLCD.bottomLCD[0] = ' ';
        }
    }
}