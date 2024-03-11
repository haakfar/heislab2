#include "heis.h"
#include "driver/elevio.h"
#include <stdlib.h>
#include <stdio.h>



int upList[4] = {0,0,0,0};
int downList[4] = {0,0,0,0};
int cabList[4] = {0,0,0,0};

int lastFloor = 0;

direction lastDirection;

direction currentDirection;

int currentTopDestination;
int currentBottomDestination;


void floorFinished(int floor){
   setUpList(floor, 0);
   setDownList(floor, 0);
   setCabList(floor, 0);
   updateLights();
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

void setLastFloor(int floor)
{
    lastFloor = floor;
}

int getLastFloor()
{
    return lastFloor;
}

void setLastDirection(direction dir)
{
    lastDirection = dir;
}

direction getLastDirection()
{
    return lastDirection;
}


direction getLastDirection();


void decideDirection()
{
    updateTopDestination();
    updateBottomDestination();
    int currentFloor = elevio_floorSensor();
    if (currentFloor != -1){
        setLastFloor(currentFloor);

        if (getDirection() == STAND_STILL)
            
        {printf("getDirection() == STAND_STILL)\n");
            if (currentTopDestination > elevio_floorSensor())
            {
                printf("currentTopDestination > elevio_floorSensor(), Going UP\n");
                setDirection(GOING_UP);
            }
            else if (currentBottomDestination < elevio_floorSensor())
            {
                printf("currentBottomDestination < elevio_floorSensor(), Going DOWN\n");
                setDirection(GOING_DOWN);
            }
        }
        else if (getDirection() == GOING_UP)
        {   printf("getDirection() == GOING_UP\n");
            if(currentTopDestination <= elevio_floorSensor())
            {
                setDirection(GOING_DOWN);
                printf("currentTopDestination <= elevio_floorSensor(), Going DOWN\n");

            }
        }else if (getDirection() == GOING_DOWN){
            if(currentBottomDestination >= elevio_floorSensor())
            {
                setDirection(GOING_UP);
                printf("currentBottomDestination >= elevio_floorSensor(), GOING_UP\n");

            }
        }
    }
};


void decideDirectionAfterStop()

{
    updateTopDestination();
    updateBottomDestination();
    int currentFloor = lastFloor;
    if (currentFloor != -1){
        

        if (lastDirection == STAND_STILL)
            
        {printf("getDirection() == STAND_STILL)\n");
            if (currentTopDestination > lastFloor)
            {
                printf("currentTopDestination > elevio_floorSensor(), Going UP\n");
                setDirection(GOING_UP);
            }
            else if (currentBottomDestination < lastFloor)
            {
                printf("currentBottomDestination < elevio_floorSensor(), Going DOWN\n");
                setDirection(GOING_DOWN);
            }
        }
        else if (lastDirection == GOING_UP)
        {   printf("getDirection() == GOING_UP\n");
            if(currentTopDestination <= lastFloor)
            {
                setDirection(GOING_DOWN);
                printf("currentTopDestination <= elevio_floorSensor(), Going DOWN\n");

            }
        }else if (lastDirection == GOING_DOWN){
            if(currentBottomDestination >= lastFloor)
            {
                setDirection(GOING_UP);
                printf("currentBottomDestination >= elevio_floorSensor(), GOING_UP\n");

            }
        }
    }
};

int hasNoFurtherCommands(){

    int totalButtonsPressed = 0;
    for (int i=0;i<N_FLOORS;i++)
    {
        totalButtonsPressed += getUpList(i);
        totalButtonsPressed += getDownList(i);
        totalButtonsPressed += getCabList(i);
    } 
    //printf("TotalButtonsPressed");
    if (totalButtonsPressed == 0){return 1;}
    else {return 0;}

}

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
    
    elevio_doorOpenLamp(1);
    floorFinished(elevio_floorSensor());
    while (1) { 





        for (int i = 0; i < 30; i++) {
            nanosleep(&(struct timespec){0, 20 * 1000 * 100}, NULL); 
            updateHighCommandLists();
            updateLights();
            



                   while(elevio_stopButton()){
                        setLastDirection(getDirection());
                        floorFinished(0);
                        floorFinished(1);
                        floorFinished(2);
                        floorFinished(3);
                        //setDirection(STAND_STILL);
                        elevio_motorDirection(DIRN_STOP);
                        elevio_doorOpenLamp(1);
                        elevio_stopLamp(1);

                        while (elevio_stopButton())
                        {
                            nanosleep(&(struct timespec){0.01}, NULL);
                            elevio_stopLamp(1);
                        }
                        elevio_stopLamp(0);

                        nanosleep(&(struct timespec){3, 0}, NULL);


                        elevio_doorOpenLamp(0);
                        while (hasNoFurtherCommands())
                        {
                            updateHighCommandLists();
                        }
                        //setDirection(STAND_STILL);
                        //elevio_motorDirection(DIRN_STOP);

                        //decideDirectionAfterStop();
                        decideDirection();
                        
                    };


            


            if (elevio_obstruction() == 1) {
               
                break;
            };
        };

        if (elevio_obstruction() != 1) {
            
            break;
        };
    };
    
    
    floorFinished(elevio_floorSensor());
    //nanosleep(&(struct timespec){3, 0}, NULL);
    


    elevio_doorOpenLamp(0);

    
    //decideDirection();
    if (hasNoFurtherCommands() == 1) 
    {setDirection(STAND_STILL);}
    
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


void checkForStopButton()
{

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

