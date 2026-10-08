#include"car.h"
void car_init(Car *car)
{
    car->speed = 0.0;
    car->mass = 1200.0;
    
    car->throttle = 0.0;
    car->brake = 0.0;
    car->clutch = 0.0;
    
    car->gear = 0;

    car->drive_force = 0.0;
    car->acceleration = 0.0;

    for (int i = 0; i < 4; i++)
    {
        car->wheels[i].angular_velocity = 0.0;
    }

}

    void car_update(Car *car , double dt)
    {
        const double max_drive_force = 2400.0;
        car->drive_force = max_drive_force * car->throttle;
        car->acceleration = car->drive_force / car->mass;
        car->speed += car->acceleration *dt;
    }
    
