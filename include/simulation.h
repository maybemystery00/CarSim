#ifndef CARSIM_SIMULATION_H
#define CARSIM_SIMULATION_H

typedef struct 
{
    double time;
    double dt;
}Simulation; 

void simulation_init(Simulation *sim,double dt);
void simulation_step(Simulation *sim);

#endif