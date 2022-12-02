#include "objects.h"
#include "properties.h"

//Public methods
gameSelf constructGameSelf(void){

};
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
     *  topLCD/bottomLCD[1 -> MAX_SIZE - 1] displays topTrack/bottomTrack
     *  
     *  1. Determine current birdPosition
     *      A. Display birdStateAlive on topLCD[0] || bottomLCD[0]
     *      B. Place a space character on opposing LCD
     *  2. Print LCD index by index
     *      A. from trackIndex [0 -> MAX_SIZE - 1]
     *          I. Append topTrack/bottomTrack[trackIndex] to topLCD/bottomLCD[trackIndex + 1]   
     */
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

