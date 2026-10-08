#ifndef CARSIM_CAR_H
#define CARSIM_CAR_H

typedef struct
{
    double angular_velocity;
}Wheel;

typedef struct 
{
    Wheel Wheels[4];

    
    double speed;
    
    double accelerator;
    double brake;
    double clutch;


    int gear;
}car;

#endif