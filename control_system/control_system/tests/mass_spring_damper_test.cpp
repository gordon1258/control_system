//
//  mass_spring_damper_test.cpp
//  control_systemUT
//
//  Created by Li-Cheng Hsu on 1/6/20.
//  Copyright © 2020 Li-Cheng Hsu. All rights reserved.
//

#include <stdio.h>
#include "gtest/gtest.h"

#include "mass_spring_damper.hpp"

class sysMSDTest_General : public testing::Test
{
public:
    sysMSD* sys;
    
    //sysMSD::state* xTest;
    //sysMSD::stateDer* xDotTest;
    
    void SetUp() override
    {
        sys = new sysMSD();
        //xTest = new sysMSD::state();
        //xDotTest = new sysMSD::stateDer();
    }
    
    void TearDown() override
    {
        delete sys;
        //delete xTest;
        //delete xDotTest;
    }
};

TEST_F(sysMSDTest_General, InitializationTest)
{
    // Arrange
    double x1 = 0;
    double x2 = 0;
    double xDot1 = 0;
    double xDot2 = 0;
    
    // Assert
    EXPECT_EQ(sys->getState().x1, x1);
    EXPECT_EQ(sys->getState().x2, x2);
    EXPECT_EQ(sys->getStateDer().xDot1, xDot1);
    EXPECT_EQ(sys->getStateDer().xDot2, xDot2);
    EXPECT_EQ(sys->getCurTime(), 0);
}


TEST_F(sysMSDTest_General, initialCondSettableTest)
{
    // Arrange
    double t0 = 1.5;
    double x1_init = 10.5;
    double x2_init = 5.3;
    
    // Act
    sys->setInitState(x1_init, x2_init);
    sys->setInitTime(t0);
    
    // Assert
    EXPECT_EQ(sys->getState().x1, x1_init);
    EXPECT_EQ(sys->getState().x2, x2_init);
    EXPECT_EQ(sys->getCurTime(), t0);
}


TEST_F(sysMSDTest_General, sampleTimeSettableTest)
{
    // Arrange
    double dt = 0.01; // sec
    
    // Act
    sys->setSampleTime(dt);
    
    // Assert
    EXPECT_EQ(sys->getSampleTime(), dt);
}

TEST_F(sysMSDTest_General, negSampleTimeTest)
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


TEST_F(sysMSDTest_General, systemProperpiesSettable)
{
    // Arrange
    double m = 1; // kg
    double b = 10; // N s/m
    double k = 20; // N/m
    
    // Act
    sys->setMass(m);
    sys->setDamper(b);
    sys->setSpring(k);
    
    // Assert
    EXPECT_EQ(sys->getMass(), m);
    EXPECT_EQ(sys->getDamper(), b);
    EXPECT_EQ(sys->getSpring(), k);
}
