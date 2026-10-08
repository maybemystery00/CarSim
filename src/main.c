#include <stdio.h>
#include "simulation.h"
#include "car.h"

int main(void)
{
    car car;
    Simulation sim;
    simulation_init(&sim,0.01);
    for (int i=0;i<10;i++)
    {
        printf("Time: %.2f s\n",sim.time);
        simulation_step(&sim);
    }

    return 0;    
}