#pragma once

typedef enum { 
    STAND_STILL = 0,
    GOING_UP      = 1,
    GOING_DOWN    = 2,
} direction;

void setDirection(direction currentDirection);
direction getDirection();
void printDirection();

void updateTopDestination();
void updateBottomDestination();
int getTopDestination();
int getBottomDestination();

void setDownList(int etasje, int status); //setter status på gitt etasje
void setUpList(int etasje, int status);
void setCabList(int etasje, int status);

int getDownList(int etasje); //returnerer status på gitt etasje
int getUpList(int etasje); 
int getCabList(int etasje);

void updateHighCommandLists();
void printCommandLists();
void updateLights();

void floorFinished(int floor);

void printCurrentTopAndBottomDestinations();

void decideDirection();
void decideDirectionAfterStop();

void pitStop();
void checkForStop();

int hasNoFurtherCommands();

void setLastFloor(int floor);
int getLastFloor();

void setLastDirection(direction dir);
direction getLastDirection();
