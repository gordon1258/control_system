//
//  veh_model_bikeKinematic.hpp
//  control_system
//
//  Created by Li-Cheng Hsu on 1/31/20.
//  Copyright © 2020 Li-Cheng Hsu. All rights reserved.
//

#ifndef veh_model_bikeKinematic_hpp
#define veh_model_bikeKinematic_hpp

#include <stdio.h>
#include "Euler.hpp"

#endif /* veh_model_bikeKinematic_hpp */

class bikeKine
{
public:
    struct point2d
    {
        double x_;
        double y_;
        
        point2d(): x_(0), y_(0) {};
        point2d(double x, double y): x_(x), y_(y) {};
    };
    
    struct spd2d
    {
        double xDot_;
        double yDot_;
        
        spd2d(): xDot_(0), yDot_(0) {};
        spd2d(double xDot, double yDot): xDot_(xDot), yDot_(yDot) {};
    };
    struct state
    {
        point2d position; // global frame
        double phi_; // angular potision
        
        state(): phi_(0) {};
    };
    
    struct stateDer
    {
        spd2d spd; // global frame
        double phiDot_; // angular speed
        
        stateDer(): phiDot_(0) {};
    };
    
    bikeKine();
    ~bikeKine();
    
    // Setter functions
    void setWheelBase(double lf, double lr);
    void setSampleTime(double dt);
    void setInitState(point2d position, double phi);
    void setInitTime(double t0);
    
    // Solver
    void kineSys(double vehVel, double steering_angle);
    
    // Getter functions
    double getCurTime() {return t_;};
    double getSampleTime() {return dt_;};
    double getFrontWheelBase() {return lf_;};
    double getRearWheelBase() {return lr_;};
    state getState() {return x_;};
    stateDer getStateDer() {return xDot_;};
    double getBeta() {return beta;};
    
private:
    // Parameters
    double lf_; // m
    double lr_; // m
    
    // Integration
    double t0_; // sec
    double dt_; // sec
    double t_; // sec, current time
    Euler* elr1; // for x_
    Euler* elr2; // for y_
    Euler* elr3; // for phi_
    
    // State
    state x_; // {X [m], Y [m], phi [rad]}
    stateDer xDot_;
    double beta;
};
