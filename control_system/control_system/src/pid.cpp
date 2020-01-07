//
//  pid.cpp
//  control_system
//
//  Created by Li-Cheng Hsu on 12/30/19.
//  Copyright © 2019 Li-Cheng Hsu. All rights reserved.
//

#include "pid.hpp"
#include <iostream>

pid::pid()
{
    dt_ = 0; // sec
    preErr = 0; // IC for error
    preIntegral = 0; // IC for integral part
    integralHold = false; // signal to hold integral
}

pid::pid(double integral_IC, double dt)
{
    dt_ = dt; // sec
    preErr = 0; // IC for error
    preIntegral = integral_IC; // IC for integral part
    integralHold = false; // signal to hold integral
}

pid::~pid() {}

void pid::setDt(double dt)
{
    if(dt <= 0)
    {
        std::cout << "The sample time is invalid!" << std::endl;
    }
    else
        dt_ = dt;
}

void pid::setGains(double kp, double ki, double kd)
{
    gains.kp = kp;
    gains.ki = ki;
    gains.kd = kd;
    
    if(gains.ki > 0)
        integralHold = true;
}
void pid::setLimits(double min, double max)
{
    if(min >= max)
        std::cout << "PID controller integral min limit is greater than max!" << std::endl;
    else
    {
        intLimits.min = min;
        intLimits.max = max;
    }
}

pid::output pid::getCmdCtrl()
{
    return data;
}

double pid::getDt()
{
    return dt_;
}

pid::ctrlGains pid::getGains()
{
    return gains;
}

pid::integralLimits pid::getIntLimits()
{
    return intLimits;
}

void pid::reset()
{
    preIntegral = 0;
    data.cmdCtrl = 0;
}
pid::output pid::pidCalculate(double err)
{
    // invalid input
    if(!checkValidity())
    {
        data.cmdCtrl = 0;
        return data;
    }
    
    double integral = preIntegral;
    if(!integralHold)
    {
        // Forward Euler
        integral += gains.ki * err * dt_;
        
        // integral term is beyond the limits
        if(integral >= intLimits.max)
            integral = intLimits.max;
        if(integral <= intLimits.min)
            integral = intLimits.min;
    }
    
    data.cmdCtrl += gains.kp * err + integral + gains.kd * (err - preErr) / dt_;
    preErr = err;
    preIntegral = integral;
    
    return data;
}

bool pid::checkValidity()
{
    if(intLimits.min >= intLimits.max)
    {
        data.isValid = false;
        std::cout << "PID controller integral min limit is greater than max!" << std::endl;
        return false;
    }
    else if(dt_ == 0)
    {
        data.isValid = false;
        std::cout << "The sample time has to be set up!" << std::endl;
        return false;
    }
    
    data.isValid = true;
    return true;
}
