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
        
        if (elevio_floorSensor() != -1){
            setLastFloor( elevio_floorSensor());
        }




        checkForStopButton();
         decideDirection();
         executeDirection();

        //int floor = elevio_floorSensor();
        //printf(" The floor is %d\n", floor);
        checkForStop();
        
        updateHighCommandLists();
        updateTopDestination();
        updateBottomDestination();

        //printf("Top Destination:  %d\n", getTopDestination() );
        //printf("Bottom Destination:  %d\n", getBottomDestination() );
        printDirection();

        updateLights();
        checkForStop();
        decideDirection();
        checkForStop();
        
        executeDirection();


        checkForStop();
        updateTopDestination();
        updateBottomDestination();
        //printf("Current time:  %d\n", time(NULL) );

    }

    return 0;
}
