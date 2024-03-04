#include "heis.h"
#include "driver/elevio.h"
#include <stdlib.h>
#include <stdio.h>



int upList[4] = {0,0,0,0};
int downList[4] = {0,0,0,0};
int cabList[4] = {0,0,0,0};

direction currentDirection;

int currentTopDestination;
int currentBottomDestination;


void floorFinished(int floor){
   setUpList(floor, 0);
   setDownList(floor, 0);
   setCabList(floor, 0);
};

int getTopDestination()
{
    return currentTopDestination;
}
int getBottomDestination()
{
    return currentBottomDestination;
}

void updateTopDestination(){
   int Top = 0;
   for (int i = 0; i < N_FLOORS; i++)
   {
      if ((downList[i] || upList[i] || cabList[i]) == 1)
      {
         if (i > Top)
         {
            Top = i;
         }
      }
   }
   currentTopDestination = Top;
};


void updateBottomDestination(){
   int Bottom = 3;
      for (int i = 0; i < N_FLOORS; i++)
      {
         if ((downList[i] || upList[i] || cabList[i]) == 1)
         {
            if (i < Bottom)
            {
               Bottom = i;
            }
         }
      }
    currentBottomDestination = Bottom;
};


void decideDirection()
{
    updateTopDestination();
    updateBottomDestination();
    int currentFloor = elevio_floorSensor();
    if (currentFloor != -1){
    if (getDirection() == STAND_STILL)
    {
        if (currentTopDestination > elevio_floorSensor())
        {
            setDirection(GOING_UP);
        }else if (currentBottomDestination<elevio_floorSensor())
        {
            setDirection(GOING_DOWN);
        }
    }else if (getDirection() == GOING_UP){
        if(currentTopDestination == elevio_floorSensor())
        {
            setDirection(GOING_DOWN);
            
        }
    }else if (getDirection() == GOING_DOWN){
        if(currentBottomDestination == elevio_floorSensor())
        {
            setDirection(GOING_UP);
        }
    }
    }
};



void checkForStop(){
    
    int floor = elevio_floorSensor();
    if (floor != -1){
      if ((cabList[floor] || (upList[floor] & (getDirection() == GOING_UP)) || (downList[floor] & (getDirection() == GOING_DOWN))) == 1)
      {
        pitStop();
      }
    }
};



void pitStop()
{
    elevio_motorDirection(DIRN_STOP);
    setDirection(STAND_STILL);
    elevio_doorOpenLamp(1);
    floorFinished(elevio_floorSensor());
    for (int i = 0; i<50;i++)
    {
        nanosleep(&(struct timespec){0,20*1000*100});
        updateHighCommandLists();
        updateLights();

    }
    
    floorFinished(elevio_floorSensor());
    //nanosleep(&(struct timespec){3, 0}, NULL);
    

    while ((elevio_stopButton() == 1) || (elevio_obstruction() == 1))
    {
        nanosleep(&(struct timespec){3, 0}, NULL);
    };
    elevio_doorOpenLamp(0);

    
    decideDirection();
};

void setDirection(direction direction)
{
    currentDirection = direction;                                    

}

direction getDirection()
{
    return currentDirection;
}

void setUpList(int etasje, int status)
{
    if (etasje != -1){
   upList[etasje] = status;
    }
};
void setDownList(int etasje, int status) //setter status på gitt etasje
{
    if (etasje != -1){
  downList[etasje] = status;
    }
};
void setCabList(int etasje, int status)
{
    if (etasje != -1){
   cabList[etasje] = status;
    }
};

int getUpList(int etasje)
{
   return upList[etasje];
};
int getDownList(int etasje) //returnerer status på gitt etasje
{
   return downList[etasje];
};
int getCabList(int etasje)
{
   return cabList[etasje];
};

void updateHighCommandLists()
{
        for (int i = 0; i< N_FLOORS; i++){
        if (elevio_callButton(i, 0) == 1)
        {
            setUpList(i,1) ;
        }
        if (elevio_callButton(i, 1) == 1)
        {
            setDownList(i,1) ;
        }
        if (elevio_callButton(i, 2) == 1)
        {
            setCabList(i,1) ;
        }

        
        //elevio_buttonLamp(int floor, ButtonType button, int value);
        }

};

void printCommandLists()
{
    for (int i = 0; i< N_FLOORS; i++){
    printf("Etasje:  %d\n", i );
    printf("UpList:  %d\n", getUpList(i) );
    printf("DownList:  %d\n", getDownList(i) );
    printf("CabList:  %d\n", getCabList(i) );
   
    }
};

void printCurrentTopAndBottomDestinations()
{
    printf("Current Top:  %d\n", currentTopDestination );
    printf("Current Bottom:  %d\n", currentBottomDestination );
};




void printDirection(){

    if (getDirection()==STAND_STILL)
    {
        printf("Direction Stand Still\n");
    }else if (getDirection()==GOING_UP)
    {
        printf("Direction Going Up\n");
    }else if(getDirection()==GOING_DOWN){
        printf("Direction Going Down\n");
    }else{
        printf("Direction undefined\n");
    }
};

void updateLights(){

   for (int i = 0; i < N_FLOORS ; i++)
   {
      elevio_buttonLamp(i, BUTTON_HALL_UP, upList[i]);
      elevio_buttonLamp(i, BUTTON_HALL_DOWN, downList[i]);
      elevio_buttonLamp(i, BUTTON_CAB, cabList[i]);
      
      
   }
           if (elevio_floorSensor()!=-1){
            elevio_floorIndicator(elevio_floorSensor());

        }
};

