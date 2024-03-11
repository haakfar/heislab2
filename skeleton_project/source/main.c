#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <stdbool.h>
#include "driver/elevio.h"
#include "heis.h"

int main(){
    elevio_init();
  

    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    int floor = elevio_floorSensor();


    while(elevio_floorSensor() == -1)

    {
        elevio_motorDirection(DIRN_UP);

    };
    printf("Elevator has entered defined state");

    elevio_motorDirection(DIRN_STOP);
    setDirection(STAND_STILL);

    while(1){
        
        
        while(elevio_stopButton()){
            if( elevio_floorSensor() != -1)
            {
                elevio_motorDirection(DIRN_STOP);
                elevio_doorOpenLamp(1);
                
                //nanosleep(&(struct timespec){3, 0}, NULL);
                for (int i = 0; i < 30; i++) {

                    nanosleep(&(struct timespec){0, 20 * 1000 * 100}, NULL); 
                    if (elevio_stopButton()){
                        elevio_stopLamp(1);
                    }else{elevio_stopLamp(0);}
                }
                elevio_doorOpenLamp(0);

            }
            setLastDirection(getDirection());
            floorFinished(0);
            floorFinished(1);
            floorFinished(2);
            floorFinished(3);
            //setDirection(STAND_STILL);
            elevio_motorDirection(DIRN_STOP);
            
            elevio_stopLamp(1);

            while (elevio_stopButton())
            {
                nanosleep(&(struct timespec){0.01}, NULL);
                elevio_stopLamp(1);
            }
              elevio_stopLamp(0);

            nanosleep(&(struct timespec){3, 0}, NULL);



            while (hasNoFurtherCommands())
            {
                updateHighCommandLists();
                
            }


            floorFinished(elevio_floorSensor());
            //setDirection(STAND_STILL);
            //elevio_motorDirection(DIRN_STOP);

            //decideDirectionAfterStop();
            decideDirection();
            
        };
    

        int floor = elevio_floorSensor();
        //printf(" The floor is %d\n", floor);
        checkForStop();
        
        updateHighCommandLists();
        updateTopDestination();
        updateBottomDestination();
        printf("Top Destination:  %d\n", getTopDestination() );
        printf("Bottom Destination:  %d\n", getBottomDestination() );
        printDirection();
        updateLights();
        checkForStop();
        decideDirection();
        checkForStop();
        
        
        
        if (getDirection() == GOING_UP)
        {
            elevio_motorDirection(DIRN_UP);
            /*
            if(elevio_obstruction()){
            elevio_stopLamp(1);
        } else {
            elevio_stopLamp(0);
        }*/
        }else if (getDirection() == GOING_DOWN)
        {
            elevio_motorDirection(DIRN_DOWN);
        }
        
        /*
        for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                int btnPressed = elevio_callButton(f, b);
                elevio_buttonLamp(f, b, btnPressed);
            }
        }
        */
        
        
        if(elevio_stopButton()){
            //elevio_motorDirection(DIRN_STOP);
            printCommandLists();
            printCurrentTopAndBottomDestinations();
            //break;
        }
        /*
        for (int i = 0; i< N_FLOORS; i++){
        int buttonCalled = elevio_callButton(i, 2);
        printf("Button number:  %d\n", i );
        printf("Button Called: %d\n", buttonCalled);
        
        //elevio_buttonLamp(int floor, ButtonType button, int value);
        }
        */


        


        checkForStop();
        updateTopDestination();
        updateBottomDestination();
        
        //nanosleep(&(struct timespec){0, 20*1000*1000}, NULL); // det originale
        //nanosleep(&(struct timespec){0, 20*1000*1}, NULL); //litt raskere
        //nanosleep(1);
    }

    return 0;
}
