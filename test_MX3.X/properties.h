/* 
 * File:   properties.h
 * Author: minht
 *
 * Created on December 2, 2022, 10:34 AM
 */

#ifndef PROPERTIES_H
#define	PROPERTIES_H
#include "objects.h"

//Public methods
gameSelf constructGameSelf(void);
void initGameElements(void);
void renderGameplay(gameSelf*);
void moveGame(gameSelf*);
int collisionGame(gameSelf*);
void renderGameEnd(gameSelf*);

//Private methods
static void moveObject(gameSelf*);
static void constructBird(Bird*);
static void constructObstacle(Obstacle*);
static void constructLCD(LCD*);
static void copyObstacleToBuffer(gameSelf*);
static void copyBufferToLCD(gameSelf*);
static void printLCD(gameSelf*);

#endif	/* PROPERTIES_H */

