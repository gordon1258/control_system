//
//  saturation.cpp
//  control_system
//
//  Created by Li-Cheng Hsu on 12/16/19.
//  Copyright © 2019 Li-Cheng Hsu. All rights reserved.
//

#include "saturation.hpp"
#include <iostream>

// saturation class definition

saturation::output::output()
{
    isValid = false;
    outputArray.clear();
}

saturation::output::~output()
{
    isValid = false;
    outputArray.clear();
}

saturation::saturation()
{
    data = new saturation::output;
}

saturation::~saturation()
{
    delete data;
}

void saturation::getInputArray(std::vector<double>& array)
{
    if(checkValid(array))
        for(int i = 0; i < array.size(); ++i)
            inputArray.push_back(array[i]);
}

void saturation::sat(double lb, double ub)
{
    if(checkValid(inputArray))
    {
        for(double num: inputArray)
        {
            if(num >= ub)
            {
                data->outputArray.push_back(ub);
                continue;
            }
            if(num <= lb)
            {
                data->outputArray.push_back(lb);
                continue;
            }
            data->outputArray.push_back(num);
        }
    }
}

void saturation::printInputArray()
{
    if(checkValid(inputArray))
    {
        std::cout << "The input array is" << std::endl;
        for(int i = 0; i < inputArray.size(); ++i)
            std::cout << inputArray[i] << std::endl;
    }
}

void saturation::printOutputArray()
{
    if(checkValid(data->outputArray))
    {
        std::cout << "The output array is" << std::endl;
        for(int i = 0; i < data->outputArray.size(); ++i)
            std::cout << data->outputArray[i] << std::endl;
    }
}

bool saturation::checkValid(std::vector<double> array)
{
    if(array.empty())
    {
        std::cout << "The input array is empty!" << std::endl;
        return false;
    }
    return true;
}
