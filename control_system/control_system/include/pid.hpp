//
//  pid.hpp
//  control_system
//
//  Created by Li-Cheng Hsu on 12/30/19.
//  Copyright © 2019 Li-Cheng Hsu. All rights reserved.
//

#ifndef pid_hpp
#define pid_hpp

#include <stdio.h>
#include <limits>

// Generic discrete-time PID controller
// Anti-windup: Default integral hold

class pid
{
public:
    struct output
    {
        bool isValid;
        double cmdCtrl;
        
        output() : cmdCtrl(0), isValid(false) {};
    };
    
    struct ctrlGains
    {
        double kp;
        double ki;
        double kd;
        
        ctrlGains() : kp(0), ki(0), kd(0) {};
    };
    
    struct integralLimits
    {
        double min;
        double max;
        
        integralLimits() : min(std::numeric_limits<double>::min()), max(std::numeric_limits<double>::max()) {};
    };
    
    pid();
    pid(double integral_IC, double dt);
    ~pid();
    
    void setDt(double dt);
    void setGains(double kp, double ki, double kd);
    void setInitCond(double integral_IC) {preIntegral = integral_IC;};
    void setLimits(double min, double max);
    
    output getCmdCtrl();
    double getDt();
    ctrlGains getGains();
    integralLimits getIntLimits();
    
    
    void reset(); // reset integral and cmdCtrl
    output pidCalculate(double err);

protected:

    double dt_; // sec
    double preErr; // IC for error
    double preIntegral; // IC for integral part
    bool integralHold; // signal to hold integral
    
    output data;
    ctrlGains gains;
    integralLimits intLimits;
    
    bool checkValidity();
};
#endif /* pid_hpp */
