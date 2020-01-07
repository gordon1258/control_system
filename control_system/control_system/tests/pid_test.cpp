//
//  pid_test.cpp
//  control_systemUT
//
//  Created by Li-Cheng Hsu on 12/31/19.
//  Copyright © 2019 Li-Cheng Hsu. All rights reserved.
//

#include <stdio.h>
#include <limits>
#include "gtest/gtest.h"
#include "pid.hpp"

class pidTest_General : public testing::Test
{
public:
    pid* pidCtrl;
    
    void SetUp() override
    {
        pidCtrl = new pid;
    }
    void TearDown() override
    {
        delete pidCtrl;
    }
};

class pidTest_Alg : public testing::Test
{
public:
    double dt = 0.1; // 100 ms
    double integral_IC = 0;
    
    pid* pidCtrl;
    
    void SetUp() override
    {
        pidCtrl = new pid(integral_IC, dt);
    }
    void TearDown() override
    {
        delete pidCtrl;
    }
};


TEST_F(pidTest_General, InitializationTest)
{
    // Assert
    EXPECT_EQ(pidCtrl->getCmdCtrl().cmdCtrl, 0);
    EXPECT_EQ(pidCtrl->getCmdCtrl().isValid, false);
    EXPECT_EQ(pidCtrl->getDt(), 0);
    EXPECT_EQ(pidCtrl->getGains().kp, 0);
    EXPECT_EQ(pidCtrl->getGains().ki, 0);
    EXPECT_EQ(pidCtrl->getGains().kd, 0);
}

TEST_F(pidTest_General,SampleTimeSettableTest_Normal)
{
    // Positive sample time
    // Arrange
    double dt = 0.1; // 100 ms
    
    // Act
    pidCtrl->setDt(dt);
    
    // Assert
    EXPECT_EQ(pidCtrl->getDt(), dt);
}

TEST_F(pidTest_General,SampleTimeSettableTest_nonPositive)
{
    // Arrange
    double dt = -1;
    
    // Act
    pidCtrl->setDt(dt);
    
    // Assert
    EXPECT_EQ(pidCtrl->getDt(), 0);
}

TEST_F(pidTest_General,IntegInitCondSettableTest_nonPositive)
{
    // Arrange
    double integral_IC = 10;
    double dt = 1;
    
    // Act
    pidCtrl->setInitCond(integral_IC);
    pidCtrl->setDt(dt);
    pidCtrl->pidCalculate(0);
    
    // Assert
    EXPECT_EQ(pidCtrl->getCmdCtrl().cmdCtrl, integral_IC);
}

TEST_F(pidTest_General, IntegralLimitsTest_Normal)
{
    // Arrange
    double max = 100;
    double min = -100;
    
    // Act
    pidCtrl->setLimits(min, max);
    
    // Assert
    EXPECT_EQ(pidCtrl->getIntLimits().min, min);
    EXPECT_EQ(pidCtrl->getIntLimits().max, max);
}

TEST_F(pidTest_General, IntegralLimitsTest_wrongSetting)
{
    // Arrange
    double max = 100, min = -100;
    double max_new = -100, min_new = 100;
    
    // Act
    pidCtrl->setLimits(min, max);
    pidCtrl->setLimits(min_new, max_new);
    
    
    // Assert
    EXPECT_EQ(pidCtrl->getIntLimits().min, min);
    EXPECT_EQ(pidCtrl->getIntLimits().max, max);
}
