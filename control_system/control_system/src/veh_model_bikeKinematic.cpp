//
//  veh_model_bikeKinematic.cpp
//  control_system
//
//  Created by Li-Cheng Hsu on 1/31/20.
//  Copyright © 2020 Li-Cheng Hsu. All rights reserved.
//

#include "veh_model_bikeKinematic.hpp"
#include <iostream>
#include <cmath>

// Constructor and destructor
bikeKine::bikeKine()
{
    lf_ = 0;
    lr_ = 0;
    
    t0_ = 0;
    dt_ = 0;
    t_ = 0;
    
    // State
    elr1 = new Euler;
    elr2 = new Euler;
    elr3 = new Euler;
    beta = 0;
}

bikeKine::~bikeKine()
{
    delete elr1;
    delete elr2;
    delete elr3;
}

// Setter functions
void bikeKine::setWheelBase(double lf, double lr)
{
    if(lf <= 0)
        std::cout << "front wheel base has to be positive!" << std::endl;
    else
        lf_ = lf;
    
    if(lr <= 0)
        std::cout << "rear wheel base has to be positive!" << std::endl;
    else
        lr_ = lr;
    
}

void bikeKine::setSampleTime(double dt)
{
    if(dt <= 0)
        std::cout << "The sample time has to be positive!" << std::endl;
    else
        dt_ = dt;
}

void bikeKine::setInitState(point2d position, double phi)
{
    x_.position = position;
    x_.phi_ = phi;
}

void bikeKine::setInitTime(double t0)
{
    if(t0 < 0)
        std::cout << "The input initial time has to be non negative!" << std::endl;
    else
    {
        t0_ = t0;
        t_ = t0_;
    }
}
   
// Solver
void bikeKine::kineSys(double vehVel, double steering_angle)
{
    // Initialization for integrator
    elr1->setSampleTime(dt_);
    elr2->setSampleTime(dt_);
    elr3->setSampleTime(dt_);
    
    elr1->setInitCond(x_.position.x_, t_);
    elr2->setInitCond(x_.position.y_, t_);
    elr3->setInitCond(x_.phi_, t_);
    
    // Set the final time for the integrator
    elr1->setFinalTime(t_ + dt_);
    elr2->setFinalTime(t_ + dt_);
    elr3->setFinalTime(t_ + dt_);
    
    // Bicycle Kinematic model: xDot calculation
    beta = atan(lf_ * tan(steering_angle) / (lf_ + lr_));
    xDot_.spd.xDot_ = vehVel * cos(x_.phi_ + beta);
    xDot_.spd.yDot_ = vehVel * sin(x_.phi_ + beta);
    xDot_.phiDot_ = vehVel * cos(beta) * tan(beta) / (lf_ + lr_);
    
    // Integral
    elr1->solver(xDot_.spd.xDot_);
    elr2->solver(xDot_.spd.yDot_);
    elr3->solver(xDot_.phiDot_);
    
    // Update the new state
    x_.position.x_ = elr1->getCurState();
    x_.position.y_ = elr2->getCurState();
    x_.phi_ = elr3->getCurState();
    
    // Update the new output
    //y_ = x.x1;
    
    // Update the new time
    t_ = elr1->getCurTime();
}
