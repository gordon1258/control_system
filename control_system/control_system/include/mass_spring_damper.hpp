//
//  mass_spring_damper.hpp
//  control_system
//
//  Created by Li-Cheng Hsu on 1/6/20.
//  Copyright © 2020 Li-Cheng Hsu. All rights reserved.
//

// A simple mass-spring-damper dynamic simulation model
// ref: <http://ctms.engin.umich.edu/CTMS/index.php?example=Introduction&section=ControlPID>

// State-space representation
// xDot = Ax + Bu
//    y = Cx

// where x = [position
//            velocity];

// where A = [   0    1;
//            -k/m -b/m]
//       B = [   0;
//              1/m]
//       C = [  1   0];


#ifndef mass_spring_damper_hpp
#define mass_spring_damper_hpp

#include <stdio.h>
#include "Euler.hpp"

class sysMSD
{
public:
    
    struct state
    {
        double x1;
        double x2;
        
        state() : x1(0), x2(0) {};
    };
    
    struct stateDer
    {
        double xDot1; // derivative of position
        double xDot2; // derivative of velocity
        
        stateDer() : xDot1(0), xDot2(0) {};
    };
    
    sysMSD();
    ~sysMSD();
    
    // setter functions
    void setMass(double m);
    void setSpring(double k);
    void setDamper(double b);
    void setSampleTime(double dt);
    void setInitState(double x1_init, double x2_init);
    void setInitTime(double t0);
    
    // Dynamic system solver
    void dynSys(double F);
    
    // getter functions
    double getMass() {return m_;};
    double getSpring() {return k_;};
    double getDamper(){return b_;};
    double getCurTime() {return t_;};
    double getSampleTime() {return dt_;};
    state getState() {return x;};
    stateDer getStateDer() {return xDot;};
    double getY() {return y_;};
    
private:
    double m_; // mass in kg
    double k_; // spring constant in N/m
    double b_; // damping constant in N s/m
    
    double y_; // output, position in this case
    
    // for integration
    double t0_;
    double dt_;
    double t_;
    Euler* elr1; // for x1
    Euler* elr2; // for x2
    
    // for states
    state x;
    stateDer xDot;
};

#endif /* mass_spring_damper_hpp */
