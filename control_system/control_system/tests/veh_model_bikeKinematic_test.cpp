//
//  veh_model_bikeKinematic_test.cpp
//  control_systemUT
//
//  Created by Li-Cheng Hsu on 1/31/20.
//  Copyright © 2020 Li-Cheng Hsu. All rights reserved.
//

#include <stdio.h>
#include "gtest/gtest.h"

#include "veh_model_bikeKinematic.hpp"

class BikeKineTest_General : public testing::Test
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

TEST_F(BikeKineTest_General, InitializationTest)
{
    // Arrange
    double x = 0;
    double y = 0;
    double phi = 0;
    double beta = 0;
    double xDot = 0;
    double yDot = 0;
    
    // Assert
    EXPECT_EQ(sys->getState().position.x_, x);
    EXPECT_EQ(sys->getState().position.y_, y);
    EXPECT_EQ(sys->getState().phi_, phi);
    EXPECT_EQ(sys->getBeta(), beta);
    EXPECT_EQ(sys->getStateDer().spd.xDot_, xDot);
    EXPECT_EQ(sys->getStateDer().spd.yDot_, yDot);
    EXPECT_EQ(sys->getStateDer().phiDot_, phi);
    EXPECT_EQ(sys->getCurTime(), 0);
}

TEST_F(BikeKineTest_General, initialCondSettableTest)
{
    // Arrange
    double t0 = 1.5;
    double x_init = 10.5;
    double y_init = 5.3;
    bikeKine::point2d initPos(x_init, y_init);
    double phi_init = 3.14;
    
    // Act
    sys->setInitState(initPos, phi_init);
    sys->setInitTime(t0);
    
    // Assert
    EXPECT_EQ(sys->getState().position.x_, x_init);
    EXPECT_EQ(sys->getState().position.y_, y_init);
    EXPECT_EQ(sys->getState().phi_, phi_init);
    EXPECT_EQ(sys->getCurTime(), t0);
}

TEST_F(BikeKineTest_General, sampleTimeSettableTest)
{
    // Arrange
    double dt = 0.01; // sec
    
    // Act
    sys->setSampleTime(dt);
    
    // Assert
    EXPECT_EQ(sys->getSampleTime(), dt);
}

TEST_F(BikeKineTest_General, negSampleTimeTest)
{
    // Arrange
    double dt = 0.1;
    // Act
    sys->setSampleTime(dt);
    
    // Assert
    EXPECT_EQ(sys->getSampleTime(), dt);
    
    // Set a negative sample time
    // Arrange
    double dt_neg = -0.1;
    // Act
    sys->setSampleTime(dt_neg);
    
    // Assert
    EXPECT_EQ(sys->getSampleTime(), dt);
}

TEST_F(BikeKineTest_General, systemProperpiesSettable)
{
    // Arrange
    double lf = 10; // m
    double lr = 10; // m
    
    // Act
    sys->setWheelBase(lf, lr);
    
    // Assert
    EXPECT_EQ(sys->getFrontWheelBase(), lf);
    EXPECT_EQ(sys->getRearWheelBase(), lr);
}
