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
    //saturation::output* data;
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
    EXPECT_EQ(false, data->data->isValid);
}

TEST_F(SaturationTest, saturationAlgTest)
{
    std:: vector<double> input = {-0.5, 5, 1000, 4, -2, 3, 4, -500};
    double lb = -10, ub = 10;

    data->getInputArray(input);
    data->sat(lb, ub);

    std:: vector<double> expectedOutput = {-0.5, 5, 10, 4, -2, 3, 4, -10};
    EXPECT_EQ(expectedOutput, data->data->outputArray);
}
