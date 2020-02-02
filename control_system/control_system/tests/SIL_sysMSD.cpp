//
//  SIL_sysMSD.cpp
//  control_systemUT
//
//  Created by Li-Cheng Hsu on 1/31/20.
//  Copyright © 2020 Li-Cheng Hsu. All rights reserved.
//

#include <stdio.h>
#include "gtest/gtest.h"

// GNUplot headers
#include "gnuplot-iostream.h"
#include <map>
#include <vector>
#include <boost/tuple/tuple.hpp>

#include "mass_spring_damper.hpp"
#include "pid.hpp"

TEST(SIL_sysMSD_pid, SIL_test_sysMSD_pid)
{
    // Mass-spring-damper system with PID controller
    sysMSD* sys;
    pid* pidCtrl;
    
    sys = new sysMSD;
    pidCtrl = new pid;
    
    // Parameters
    double t0 = 0;
    double dt_plant = 0.1; // sec
    double tFinal = 10; // sec
    double x_init = 0; // m
    double v_init = 0; // m/s
    
    double m = 1; // kg
    double b = 10; // N s/m
    double k = 20; // N/m
    
    double kp = 3;
    double ki = 0.01;
    double kd = 0;
    double dt_C = 0.01;
    
    std::vector<std::pair<double,double>> x_t;
    std::vector<std::pair<double,double>> v_t;
    std::vector<std::pair<double,double>> y_t;
    std::vector<std::pair<double,double>> err_t;
    std::vector<std::pair<double,double>> F_t;
    std::vector<std::pair<double,double>> xDes_t;
    
    
    // Init
    sys->setInitTime(t0);
    sys->setSampleTime(dt_plant);
    sys->setInitState(x_init, v_init);
    
    sys->setMass(m);
    sys->setDamper(b);
    sys->setSpring(k);
    
    std::cout << "t = " << sys->getCurTime() << std::endl;
    std::cout << "x = " << sys->getState().x1 << std::endl;
    x_t.push_back(std::make_pair(sys->getCurTime(), sys->getState().x1));
    v_t.push_back(std::make_pair(sys->getCurTime(), sys->getState().x2));
    y_t.push_back(std::make_pair(sys->getCurTime(), sys->getY()));
    
    // PID control
    double x_des = 1;
    xDes_t.push_back(std::make_pair(sys->getCurTime(), x_des));
    err_t.push_back(std::make_pair(sys->getCurTime(), x_des - sys->getState().x1));
    
    pidCtrl->setDt(dt_C);
    pidCtrl->setGains(kp, ki, kd);
    double F = pidCtrl->getCmdCtrl().cmdCtrl;
    F_t.push_back(std::make_pair(sys->getCurTime(), F));
    
    // Simulation starts
    while(sys->getCurTime() < tFinal)
    {
        
        sys->dynSys(F);
        
        // Update F with PID controller
        double err = x_des - sys->getState().x1;
        pidCtrl->pidCalculate(err);
        
        if(pidCtrl->getCmdCtrl().isValid)
            F = pidCtrl->getCmdCtrl().cmdCtrl;
        
        // Push the states, outputs, and errors for plotting
        std::cout << "t = " << sys->getCurTime() << ", ";
        std::cout << "x = " << sys->getState().x1 << std::endl;
        x_t.push_back(std::make_pair(sys->getCurTime(), sys->getState().x1));
        v_t.push_back(std::make_pair(sys->getCurTime(), sys->getState().x2));
        y_t.push_back(std::make_pair(sys->getCurTime(), sys->getY()));
        F_t.push_back(std::make_pair(sys->getCurTime(), F));
        xDes_t.push_back(std::make_pair(sys->getCurTime(), x_des));
        err_t.push_back(std::make_pair(sys->getCurTime(), err));
        
    }
    
    // Plot : gnuplot
    Gnuplot gp;
    
    //gp << "set xrange [0:3]\n";
    gp << "set multiplot layout 3, 1 title 'Mass-Spring-Damper with PID controller'"
         << "font ',15'" << std::endl;
    
    // plot 1: Pos
    gp << "set title 'Position'" << "font ',11'" << std::endl;
    gp << "set xlabel 'time [sec]'" << std::endl;
    gp << "set ylabel 'position [m]'" << std::endl;
    gp << "plot '-' with lines title 'position', '-' with lines title 'pos_{des}'"<<std::endl;
    gp.send1d(x_t);
    gp.send1d(xDes_t);
    
    // plot 2: Err
    gp << "set title 'Error'" << "font ',11'" << std::endl;
    gp << "set xlabel 'time [sec]'" << std::endl;
    gp << "set ylabel 'err [m]'" << std::endl;
    gp << "plot '-' with lines title 'err'"<<std::endl;
    gp.send1d(err_t);
    
    // plot 3: Force
    gp << "set title 'Force'" << "font ',11'" << std::endl;
    gp << "set xlabel 'time [sec]'" << std::endl;
    gp << "set ylabel 'force [N]'" << std::endl;
    gp << "plot '-' with lines title 'force'"<<std::endl;
    gp.send1d(F_t);
}
