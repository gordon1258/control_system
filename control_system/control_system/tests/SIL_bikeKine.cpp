//
//  SIL_bikeKine.cpp
//  control_systemUT
//
//  Created by Li-Cheng Hsu on 2/1/20.
//  Copyright © 2020 Li-Cheng Hsu. All rights reserved.
//

#include <stdio.h>

#include "gtest/gtest.h"

// GNUplot headers
#include "gnuplot-iostream.h"
#include <map>
#include <vector>
#include <boost/tuple/tuple.hpp>

#include "veh_model_bikeKinematic.hpp"
#include "pid.hpp"

class SIL_bikeKine : public testing::Test
{
public:
    bikeKine* sys;
    
    void SetUp() override
    {
        sys = new bikeKine();
    }
    
    void TearDown() override
    {
        delete sys;
    }
    
};

TEST_F(SIL_bikeKine, SIL_step)
{
    // Step response for the kinematic bicycle model
    
    // Parameters
    double t0 = 0;
    double dt_plant = 0.01; // sec
    double tFinal = 100; // sec
    
    double lf = 1.105; // m
    double lr = 1.738; // m
    
    // Init condition
    double x0 = 0;
    double y0 = 0;
    double phi0 = 0;
    bikeKine::point2d initState(x0, y0);
    
    // Plot container
    std::vector<std::pair<double, double>> pos;
    std::vector<std::pair<double, double>> X_t;
    std::vector<std::pair<double, double>> Y_t;
    std::vector<std::pair<double, double>> phi_t;
    std::vector<std::pair<double, double>> beta_t;
    // Plot container: Input
    std::vector<std::pair<double, double>> V_t;
    std::vector<std::pair<double, double>> steering_t;
    
    
    // Init
    sys->setInitState(initState, phi0);
    sys->setInitTime(t0);
    sys->setSampleTime(dt_plant);
    
    sys->setWheelBase(lf, lr);
    
    // Plot init
    pos.push_back(std::make_pair(sys->getState().position.x_, sys->getState().position.y_));
    X_t.push_back(std::make_pair(sys->getCurTime(), sys->getState().position.x_));
    Y_t.push_back(std::make_pair(sys->getCurTime(), sys->getState().position.y_));
    phi_t.push_back(std::make_pair(sys->getCurTime(), sys->getState().phi_));
    beta_t.push_back(std::make_pair(sys->getCurTime(), sys->getBeta()));
    
    // Speed and steering profile
    double V_veh = 5; // m/s
    double steering = sin(sys->getCurTime());
    V_t.push_back(std::make_pair(sys->getCurTime(), V_veh));
    steering_t.push_back(std::make_pair(sys->getCurTime(), steering));
    
    while(sys->getCurTime() <= tFinal)
    {
        steering = sin(sys->getCurTime());
        sys->kineSys(V_veh, steering);
        
        // Push the states to the container for plot
        pos.push_back(std::make_pair(sys->getState().position.x_, sys->getState().position.y_));
        X_t.push_back(std::make_pair(sys->getCurTime(), sys->getState().position.x_));
        Y_t.push_back(std::make_pair(sys->getCurTime(), sys->getState().position.y_));
        phi_t.push_back(std::make_pair(sys->getCurTime(), sys->getState().phi_));
        beta_t.push_back(std::make_pair(sys->getCurTime(), sys->getBeta()));
        V_t.push_back(std::make_pair(sys->getCurTime(), V_veh));
        steering_t.push_back(std::make_pair(sys->getCurTime(), steering));
        
        std::cout << "t = " << sys->getCurTime() << ", ";
        std::cout << "x = " << pos.back().first << ", ";
        std::cout << "y = " << pos.back().second << std::endl;
    }
    
    // Plot: gnuplot
    Gnuplot gp_pos;
    
    gp_pos << "set multiplot layout 1, 1 title 'Bicycle Kinematic Model - Position'" << "font ',15'" << std::endl;
    
    // plot 1: Pos
    gp_pos << "set title 'Position of C.G. '" << "font ',11'" << std::endl;
    gp_pos << "set xlabel 'X [m]'" << std::endl;
    gp_pos << "set ylabel 'Y [m]'" << std::endl;
    gp_pos << "plot '-' with lines title 'position'"<<std::endl;
    gp_pos.send1d(pos);
    
    // plot 2: Time response
    Gnuplot gp;
    
    gp << "set multiplot layout 3, 1 title 'Bicyle Kinematic Model - Response'"
         << "font ',15'" << std::endl;
    
    /*
    // plot 2.1: X V.S. t
    gp << "set title 'Vehicle Position X'" << "font ' ,11'" << std::endl;
    gp << "set xlabel 't [sec]'" << std::endl;
    gp << "set ylabel 'X [m]'" << std::endl;
    gp << "plot '-' with lines title 'veh heading'"<<std::endl;
    gp.send1d(X_t);

    // plot 2.2: Y V.S. t
    gp << "set title 'Vehicle Position Y'" << "font ' ,11'" << std::endl;
    gp << "set xlabel 't [sec]'" << std::endl;
    gp << "set ylabel 'Y [m]'" << std::endl;
    gp << "plot '-' with lines title 'veh heading'"<<std::endl;
    gp.send1d(Y_t);
    */
     
    // plot 2.3: Veh heading
    gp << "set title 'Vehicle Heading'" << "font ' ,11'" << std::endl;
    gp << "set xlabel 't [sec]'" << std::endl;
    gp << "set ylabel 'phi [rad]'" << std::endl;
    gp << "plot '-' with lines title 'veh heading'"<<std::endl;
    gp.send1d(phi_t);
    
    // plot 2.4: Veh speed
    gp << "set title 'Vehicle Speed'" << "font ' ,11'" << std::endl;
    gp << "set xlabel 't [sec]'" << std::endl;
    gp << "set ylabel 'V_{veh} [m/s]'" << std::endl;
    gp << "plot '-' with lines title 'veh heading'"<<std::endl;
    gp.send1d(V_t);
    
    // plot 2.5: Steering
    gp << "set title 'Vehicle Steering'" << "font ' ,11'" << std::endl;
    gp << "set xlabel 't [sec]'" << std::endl;
    gp << "set ylabel 'Steering [rad]'" << std::endl;
    gp << "plot '-' with lines title 'veh heading'"<<std::endl;
    gp.send1d(steering_t);
}
