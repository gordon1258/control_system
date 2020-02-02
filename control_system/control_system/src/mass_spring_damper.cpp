//
//  mass_spring_damper.cpp
//  control_system
//
//  Created by Li-Cheng Hsu on 1/6/20.
//  Copyright © 2020 Li-Cheng Hsu. All rights reserved.
//

#include "mass_spring_damper.hpp"
#include <iostream>

sysMSD::sysMSD()
{
    m_ = 0;
    k_ = 0;
    b_ = 0;
    
    t0_ = 0;
    dt_ = 0;
    t_ = 0;
    y_ = 0;
    
    elr1 = new Euler;
    elr2 = new Euler;
}

sysMSD::~sysMSD()
{
    delete elr1;
    delete elr2;
}

void sysMSD::setMass(double m)
{
    if(m < 0)
        std::cout << "The mass has to be non-negative!" << std::endl;
    else
        m_ = m;
}
void sysMSD::setSpring(double k)
{
    if(k < 0)
        std::cout << "The spring constant has to be non-negative!" << std::endl;
    else
        k_ = k;
}
void sysMSD::setDamper(double b)
{
    if(b < 0)
        std::cout << "The damping constant has to be non-negative!" << std::endl;
    else
        b_ = b;
}

void sysMSD::setSampleTime(double dt)
{
    if(dt <=0)
        std::cout << "The input sample time has to be greater than 0!" << std::endl;
    else
        dt_ = dt;
}

void sysMSD::setInitState(double x1_init, double x2_init)
{
    x.x1 = x1_init;
    x.x2 = x2_init;
    
    y_ = x.x1;
}

void sysMSD::setInitTime(double t0)
{
    if(t0 < 0)
        std::cout << "The input initial time has to be non negative!" << std::endl;
    else
    {
        t0_ = t0;
        t_ = t0_;
    }
}

void sysMSD::dynSys(double F)
{
    
    // Initialization for integrator
    elr1->setSampleTime(dt_);
    elr2->setSampleTime(dt_);
    
    elr1->setInitCond(x.x1, t_);
    elr2->setInitCond(x.x2, t_);
    
    // Set the final time for the integrator
    elr1->setFinalTime(t_ + dt_);
    elr2->setFinalTime(t_ + dt_);
    
    // Mass-spring-damper system dynamics: xDot calculation
    xDot.xDot1 = x.x2;
    xDot.xDot2 = -(k_ / m_) * x.x1 - (b_ / m_) * x.x2 + (F / m_);
    
    // Integral
    elr1->solver(xDot.xDot1);
    elr2->solver(xDot.xDot2);
    
    // Update the new state
    x.x1 = elr1->getCurState();
    x.x2 = elr2->getCurState();
    
    // Update the new output
    y_ = x.x1;
    
    // Update the new time
    t_ = elr1->getCurTime();
}

