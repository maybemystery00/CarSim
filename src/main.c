#include <stdio.h>
#include "simulation.h"
#include "car.h"

int main(void)
{
    
    Simulation sim;
    Car car;
    simulation_init(&sim,0.01);
    for (int i=0;i<10;i++)
    {
        printf("Time: %.2f s\n",sim.time);
        simulation_step(&sim);

        car_init(&car);
        car.throttle = 1.0;
    }

    return 0;    
}