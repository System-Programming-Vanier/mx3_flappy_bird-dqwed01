/**
   	FileName:     
	
 
	Description: 
      
 * * REVISION HISTORY:
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Author        	Date            Comments on this revision
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *      
 * 
 * 		
 *******************************************************************************/

#include <xc.h>
#include "console.h"
#include "Tick_core.h"
#include "util.h"
#include <stdio.h>
#include "config.h"
#include "objects.h"
#include "properties.h"

/*
 *      1. Initialize components
 *      2. Display Objects
 *      4. Handle Objects
 *          a. Handle Inputs
 *              I. Move bird accordingly if there is an input and play a sound
 *              II. Do nothing if there isn't an input
 *          b. Move obstacles every 250ms
 *      5. Handle Collision
 *          a. If Collision end game
 *              I. Stop movement of game
 *              II. Play sound
 *              III. Rotate bird every 125ms 
 *          b. If no Collision continue game
 */

int main( void){
    setbuf(stdout, NULL); // Disable buffered outputs.  Needed in C++
#ifdef SIMULATION
    uart4_init();
    stdio_set(C_UART4);
#else
    lcd_init();
    stdio_set(C_LCD);
#endif
    //Init Components
    init_heartbeat();
    initGameElements();
    init_tone();
    gameSelf game = constructGameSelf();
    int stamp = tick_get();
    tone_high(1000);
    //Game is active
    while(1){
        heartbeat(); // periodic skip counter to blink a blue LED
        if(tick_diff(stamp) >= TEN_MS){
            stamp = tick_get();

            renderGameplay(&game); //Display objects 
            moveGame(&game); //Handle Input
            }
        if (!collisionGame(&game)) break;
    }
    
        
    //Game over
    while(1){
        //Toggle Bird every 125ms
        heartbeat(); // periodic skip counter to blink a blue LED
        if (tick_diff(stamp) >= TEN_MS){
            stamp = tick_get();
            renderGameEnd(&game);
        }
    }
    return 0;
}// main

