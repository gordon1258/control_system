//
//  Euler_test.cpp
//  control_systemUT
//
//  Created by Li-Cheng Hsu on 1/6/20.
//  Copyright © 2020 Li-Cheng Hsu. All rights reserved.
//

#include <stdio.h>
#include "gtest/gtest.h"
#include "Euler.hpp"

class EulerTest_General : public testing::Test
{
public:
    Euler* elr;
    
    void SetUp() override
    {
        elr = new Euler();
    }
    void TearDown() override
    {
        delete elr;
    }
};

class EulerTest_Alg : public testing::Test
{
public:
    Euler* elr;
    
    void SetUp() override
    {
        elr = new Euler();
        elr->setSampleTime(dt);
        elr->setInitCond(x0, t0);
    }
    
    void TearDown() override
    {
        delete elr;
    }
public:
    double dt = 1; // sec
    double x0 = 0;
    double t0 = 0;
};

TEST_F(EulerTest_General, InitializationTest)
{
    // Assert
    EXPECT_EQ(elr->getCurState(), 0);
    EXPECT_EQ(elr->getCurTime(), 0);
    EXPECT_EQ(elr->getSampleTime(), 0);
}

TEST_F(EulerTest_General, initialCondSettableTest)
{
    // Arrange
    double t0 = 1.5;
    double x0 = 10.5;
    
    // Act
    elr->setInitCond(x0, t0);
    
    // Assert
    EXPECT_EQ(elr->getCurState(), x0);
    EXPECT_EQ(elr->getCurTime(), t0);
}

TEST_F(EulerTest_General, sampleTimeSettableTest)
{
    // Arrange
    double dt = 0.01; // sec
    
    // Act
    elr->setSampleTime(dt);
    
    // Assert
    EXPECT_EQ(elr->getSampleTime(), dt);
}

TEST_F(EulerTest_General, setSampleTimeReqTest)
{
    // Arrange
    double xDot = 1;
    // Act
    elr->solver(xDot);
    
    // Assert
    EXPECT_EQ(elr->getCurState(), 0); // solver wouldn't be triggered
    EXPECT_EQ(elr->getCurState(), 0); // solver wouldn't be triggered
}

TEST_F(EulerTest_Alg, setFinalTimeReqTest)
{
    // Arrange
    double xDot = 1;
    // Act
    elr->solver(xDot);
    
    // Assert
    EXPECT_EQ(elr->getCurState(), 0);
    EXPECT_EQ(elr->getCurState(), 0);
}

/*
TEST_F(EulerTest_Alg, finalTimeSetWrongReqTest)
{
    // Arrange
    double xDot = 1;
    double tFinal = 1.5; // dt = 1 sec
    // Act
    elr->setFinalTime(tFinal);
    elr->solver(xDot);
    
    // Assert
    EXPECT_EQ(elr->getCurState(), 0); // solver wouldn't operate since tFinal is not the multiple of sample time 1
    EXPECT_EQ(elr->getCurState(), 0);
}
*/

TEST_F(EulerTest_Alg, solverTest)
{
    // Arrange
    double x0 = 1, t0 = 1;
    double xDot = 1;
    double tFinal = 10;
    
    // Act
    elr->setInitCond(x0, t0);
    elr->setFinalTime(tFinal);
    elr->solver(xDot);
    
    
    // Assert
    EXPECT_EQ(elr->getCurState(), x0 + (tFinal - t0) * xDot);
    EXPECT_EQ(elr->getCurTime(), tFinal);
}
