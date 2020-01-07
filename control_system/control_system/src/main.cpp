//
//  main.cpp
//  control_system
//
//  Created by Li-Cheng Hsu on 12/16/19.
//  Copyright © 2019 Li-Cheng Hsu. All rights reserved.
//

#include <iostream>
#include "gtest/gtest.h"

#include "gnuplot-iostream.h"
#include <map>
#include <vector>
#include <boost/tuple/tuple.hpp>

#include <Eigen/Dense>

#include "mass_spring_damper.hpp"

int main(int argc, const char * argv[]) {
    
    // Mass-spring-damper system
    sysMSD* sys;
    sys = new sysMSD;
    
    // Parameters
    double t0 = 0;
    double dt = 0.1; // sec
    double tFinal = 2.5; // sec
    double x_init = 0; // m
    double v_init = 0; // m/s
    
    double m = 1; // kg
    double b = 10; // N s/m
    double k = 20; // N/m
    
    std::vector<std::pair<double,double>> x_t;
    std::vector<std::pair<double,double>> v_t;
    std::vector<std::pair<double,double>> y_t;
    
    // Init
    sys->setInitTime(t0);
    sys->setSampleTime(dt);
    sys->setInitState(x_init, v_init);
    
    sys->setMass(m);
    sys->setDamper(b);
    sys->setSpring(k);
    
    x_t.push_back(std::make_pair(sys->getCurTime(), sys->getState().x1));
    v_t.push_back(std::make_pair(sys->getCurTime(), sys->getState().x2));
    y_t.push_back(std::make_pair(sys->getCurTime(), sys->getY()));
    
    // Step reponse
    double F = 1; // N
    
    while(sys->getCurTime() < tFinal)
    {
        sys->dynSys(F);
        
        // Push the states and output for plotting
        x_t.push_back(std::make_pair(sys->getCurTime(), sys->getState().x1));
        v_t.push_back(std::make_pair(sys->getCurTime(), sys->getState().x2));
        y_t.push_back(std::make_pair(sys->getCurTime(), sys->getY()));
    }
    
    // Plot : gnuplot
    Gnuplot gp;
    
    //gp << "set xrange [0:10]\n";
    gp << "plot '-' with lines title 'position', '-' with lines title 'velocity'"<<std::endl;
    gp.send1d(x_t);
    gp.send1d(v_t);
    
    return 0;
}
