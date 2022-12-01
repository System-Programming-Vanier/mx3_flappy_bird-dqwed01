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



int main( void){
    setbuf(stdout, NULL); // Disable buffered outputs.  Needed in C++
#ifdef SIMULATION
    uart4_init();
    stdio_set(C_UART4);
#else
    lcd_init();
    stdio_set(C_LCD);
#endif    
    heartbeat_init();
    printf("\n\rHello");
    
    while (1) {
        heartbeat(); // periodic skip counter to blink a blue LED
    } //while
    return 0;
}// main

