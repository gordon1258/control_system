//
//  Euler.hpp
//  control_system
//
//  Created by Li-Cheng Hsu on 1/6/20.
//  Copyright © 2020 Li-Cheng Hsu. All rights reserved.
//

#ifndef Euler_hpp
#define Euler_hpp

#include <stdio.h>

#endif /* Euler_hpp */

class Euler
{
public:
    Euler(): t0_(0), dt_(0), t_(0), tFinal_(0), x_(0) {};
    //Euler(dt, tFinal, x0, t0): dt_(dt), tFinal_(tFinal), x0_(x0), t0_(t0) {};
    ~Euler() {};
    
    void setSampleTime(double dt);
    void setFinalTime(double tFinal);
    void setInitCond(double x0, double t0);
    
    void solver(double xDot);
    
    double getSampleTime();
    double getCurTime();
    //double getFinalTime();
    double getCurState();
    
protected:
    double t0_; // Initial time in sec
    double dt_; // Sample time (step size) in sec
    double t_; // Current time in sec
    double tFinal_; // Final time in sec
    
    double x_; // Current state
    
    bool checkValidity();
    
};
