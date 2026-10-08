#include "simulation.h"
void simulation_init(Simulation *sim, double dt)
{
    sim->time=0.0;
    sim->dt=dt;
}

void simulation_step(Simulation *sim)
{
    sim->time +=sim->dt;
}