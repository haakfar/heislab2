#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <stdbool.h>
#include "driver/elevio.h"
#include "heis.h"
/*


*/
int main(){
    elevio_init();
  

    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    int floor = elevio_floorSensor();


    while(elevio_floorSensor() == -1)

    {
        elevio_motorDirection(DIRN_UP);

    }
    

    elevio_motorDirection(DIRN_STOP);

    while(1){
        int floor = elevio_floorSensor();
        //printf(" The floor is %d\n", floor);
        


        /*
        for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                int btnPressed = elevio_callButton(f, b);
                elevio_buttonLamp(f, b, btnPressed);
            }
        }
        */
        if(elevio_obstruction()){
            elevio_stopLamp(1);
        } else {
            elevio_stopLamp(0);
        }
        
        if(elevio_stopButton()){
            elevio_motorDirection(DIRN_STOP);
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
        updateHighCommandLists();
        updateTopDestination();
        updateBottomDestination();
        updateLights();
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL); // det originale
        //nanosleep(&(struct timespec){0, 20*1000*1}, NULL); //litt raskere
        //nanosleep(1);
    }

    return 0;
}
