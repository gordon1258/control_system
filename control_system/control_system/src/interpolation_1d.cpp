//
//  interpolation_1d.cpp
//  control_system
//
//  Created by Li-Cheng Hsu on 12/22/19.
//  Copyright © 2019 Li-Cheng Hsu. All rights reserved.
//

#include <iostream>
#include "interpolation_1d.hpp"

void interpolation_1d::setX(std::vector<double> X_table)
{
    X = X_table;
}

void interpolation_1d::setY(std::vector<double> Y_table)
{
    Y = Y_table;
}
void interpolation_1d::intrp_1d(double x)
{
    if(!checkValidity()) return;
    
    // Step1: Find the correponding x position in X_table
    // Clamp method if x is out of range
    double x_min = X.front(), x_max = X.back();
    double y_min = Y.front(), y_max = Y.front();
    
    if(x >= x_max)
    {
        data.y = Y.back();
        data.isValid = true;
        return;
    }
    if(x <= x_min)
    {
        data.y = Y.front();
        data.isValid = true;
        return;
    }
    // Search for the x position
    double x_start = x_min, x_end = x_max;
    double y_start = y_min, y_end = y_max;
    
    // Binary search
    int n = X.size();
    int l = 0, r = n - 1;
    while(l < r)
    {
        int m = l + (r - l)/2;
        
        if(x > X[m + 1]) l = m + 1;
        else if(x < X[m]) r = m;
        else // (X[m] <= x <= X[m+1])
        {
            x_start = X[m];
            y_start = Y[m];
            x_end = X[m + 1];
            y_end = Y[m + 1];
            break;
        }
    }
    
    // Step2: Interpolate the value
    data.y = y_end - (x_end - x)*(y_end - y_start)/(x_end - x_start);
    data.isValid = true;
    
}

interpolation_1d::output interpolation_1d::getOutput() const
{
    return data;
}

bool interpolation_1d::checkValidity()
{
    if(X.empty())
    {
        std::cout << "Need to set X_table!" << std::endl;
        return false;
    }
    
    if(Y.empty())
    {
        std::cout << "Need to set Y_table!" << std::endl;
        return false;
    }
    
    if(X.size() != Y.size())
    {
        std::cout << "The X_table and the Y_table have to be the same size!" << std::endl;
        return false;
    }
    
    if(X.size() <= 1)
    {
        std::cout << "The size of the tables has to be greater than 1!" << std::endl;
        return false;
    }
    return true;
}

bool interpolation_1d::checkXOrder()
{
    if(checkValidity())
        return false;
    
    for(int i = 1; i < X.size(); ++i)
    {
        if(X[i-1] >= X[i])
        {
            std::cout << "X_table has to be in ascending order!" << std::endl;
            return false;
        }
    }
    return true;
}
