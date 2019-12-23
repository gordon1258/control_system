//
//  saturation_test.cpp
//  control_systemUT
//
//  Created by Li-Cheng Hsu on 12/18/19.
//  Copyright © 2019 Li-Cheng Hsu. All rights reserved.
//

#include <stdio.h>
#include "gtest/gtest.h"
#include "saturation.hpp"

class SaturationTest : public :: testing::Test
{
public:
    saturation* data;
    
    void SetUp() override
    {
        data = new saturation;
    }
    
   void TearDown() override
    {
        delete data;
    }
    
    
};


TEST_F(SaturationTest, isValidStart)
{
    // Assert
    EXPECT_EQ(data->data->isValid, false);
}

TEST_F(SaturationTest, outputArrayStart)
{
    // Arrange
    std::vector<double> expOutputArray;
    
    // Assert
    EXPECT_EQ(data->getOutputArray(), expOutputArray);
}

TEST_F(SaturationTest, saturationAlgTest_Boundary)
{
    // Arrange
    std:: vector<double> input = {-0.5, 5, 1000, 4, -2, 3, 4, -500};
    double lb = -10, ub = 10;
    std:: vector<double> v_lb (input.size(), lb);
    std:: vector<double> v_ub (input.size(), ub);

    // Act
    data->setInputArray(input);
    data->sat(lb, ub);

    // Assert
    EXPECT_GE(data->getOutputArray(), v_lb);
    EXPECT_LE(data->getOutputArray(), v_ub);
}
