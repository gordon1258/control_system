//
//  Euler.cpp
//  control_system
//
//  Created by Li-Cheng Hsu on 1/6/20.
//  Copyright © 2020 Li-Cheng Hsu. All rights reserved.
//

#include "Euler.hpp"
#include "iostream"
#include <math.h>

void Euler::setSampleTime(double dt)
{
    if(dt <=0)
        std::cout << "The input sample time has to be greater than 0!" << std::endl;
    else
        dt_ = dt;
}
void Euler::setFinalTime(double tFinal)
{
    if(tFinal < t0_)
        std::cout << "The input final time has to be greater than the initial time!" << std::endl;
    else
        tFinal_ = tFinal;
}
void Euler::setInitCond(double x0, double t0)
{
    x_ = x0;
    
    if(t0 < 0)
        std::cout << "The input initial time has to be non negative!" << std::endl;
    else
    {
        t0_ = t0;
        t_ = t0_;
    }
}

void Euler::solver(double xDot)
{
    // solver function here
    
    if(checkValidity())
    {
        while(t_ < tFinal_)
        {
            x_ += xDot * dt_;
            t_ += dt_;
        }
    }
}

double Euler::getSampleTime()
{
    std::cout << "The sample time is " << dt_ << std::endl;
    return dt_;
}
double Euler::getCurTime()
{
    std::cout << "The current time is " << t_ << std::endl;
    return t_;
}
double Euler::getCurState()
{
    std::cout << "The current state is " << x_ << std::endl;
    return x_;
}

bool Euler::checkValidity()
{
    if(dt_ <= 0)
    {
        std::cout << "Please set the sample time using setSampleTime function!" << std::endl;
        return false;
    }
    if(tFinal_ != 0 && dt_ != 0 && remainder(tFinal_, dt_) != 0)
    {
        std::cout << "The final time has to be the multiple of the sample time!" << std::endl;
        return false;
    }
    return true;
}
