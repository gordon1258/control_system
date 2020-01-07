//
//  interpolation_1d_test.cpp
//  control_systemUT
//
//  Created by Li-Cheng Hsu on 12/22/19.
//  Copyright © 2019 Li-Cheng Hsu. All rights reserved.
//

#include <stdio.h>
#include "gtest/gtest.h"
#include "interpolation_1d.hpp"


class interpolation_1dTest_General : public :: testing::Test
{
public:
    interpolation_1d* data;
    
    void SetUp() override
    {
        data = new interpolation_1d;
    }
    
    void TearDown() override
    {
        delete data;
    }
};

class interpolation_1dTest_Alg : public :: testing::Test
{
public:
    interpolation_1d* data;
    std::vector<double> X = {1,2,3,4,5};
    std::vector<double> Y = {3,2,5,2,4};
    
    void SetUp() override
    {
        data = new interpolation_1d;
        data->setX(X);
        data->setY(Y);
    }
    
    void TearDown() override
    {
        delete data;
    }
};

TEST_F(interpolation_1dTest_General, InitializationTest)
{
    // Assert
    EXPECT_EQ(data->data.y, NULL);
    EXPECT_EQ(data->data.isValid, false);
}

TEST_F(interpolation_1dTest_General, emptyTableTest)
{
    // Assert
    EXPECT_EQ(data->getOutput().isValid, false);
}

TEST_F(interpolation_1dTest_General, unequalSizeTableTest)
{
    // Arrange
    std::vector<double> X = {0, 2, 4, 6, 8};
    std::vector<double> Y = {2, 1, 3, 4, 5, 6};
    
    // Act
    data->setX(X);
    data->setY(Y);
    
    // Assert
    EXPECT_EQ(data->getOutput().isValid, false);
}

TEST_F(interpolation_1dTest_General, nonAscendingXTableTest)
{
    // Arrange
    std::vector<double> X = {3, 2, 4, 6, 8};
    std::vector<double> Y = {2, 3, 4, 2, 1};
    
    // Act
    data->setX(X);
    data->setY(Y);
    
    // Assert
    EXPECT_EQ(data->getOutput().isValid, false);
}

TEST_F(interpolation_1dTest_Alg, intrp1dAlgTest1_Normal)
{
    // Arrange
    double x = 4.5;
    double yExp = 3;
    
    // Act
    data->intrp_1d(x);
    
    // Assert
    ASSERT_EQ(data->getOutput().isValid, true);
    EXPECT_EQ(data->getOutput().y, yExp);
}

TEST_F(interpolation_1dTest_Alg, intrp1dAlgTest1_OutOfRange_ClampUB)
{
    // Arrange
    double x = 500;
    double yExp = 4;
    
    // Act
    data->intrp_1d(x);
    
    // Assert
    ASSERT_EQ(data->getOutput().isValid, true);
    EXPECT_EQ(data->getOutput().y, yExp);
}

TEST_F(interpolation_1dTest_Alg, intrp1dAlgTest1_OutOfRange_ClampLB)
{
    // Arrange
    double x = -50;
    double yExp = 3;
    
    // Act
    data->intrp_1d(x);
    
    // Assert
    ASSERT_EQ(data->getOutput().isValid, true);
    EXPECT_EQ(data->getOutput().y, yExp);
}
