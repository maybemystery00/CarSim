#ifndef CARSIM_CAR_H
#define CARSIM_CAR_H

typedef struct
{
    double angular_velocity;
}Wheel;

typedef struct 
{
    Wheel wheels[4];

    
    double speed;
    double mass;
    
    double throttle;
    double brake;
    double clutch;

    double drive_force;
    double acceleration;

    int gear;
}Car;

void car_init(Car *car);
void car_update(Car *car, double dt);
#endif