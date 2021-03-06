//
//  saturation.hpp
//  control_system
//
//  Created by Li-Cheng Hsu on 12/16/19.
//  Copyright © 2019 Li-Cheng Hsu. All rights reserved.
//

#ifndef saturation_hpp
#define saturation_hpp

#include <stdio.h>
#include <vector>

// saturation class declaration
class saturation
{
public:
    
    struct output
    {
        std::vector<double> outputArray;
        bool isValid;
        
        output();
        ~output();
    };
    
    output* data;
    
    saturation();
    ~saturation();
    void setInputArray(std::vector<double>& array);
    std::vector<double> getOutputArray() const;
    bool getOutputValid() const;
    void sat(double lb, double ub);
    void printInputArray();
    void printOutputArray();
    
private:
    std::vector<double> inputArray;
    
    bool checkValid(std::vector<double> array);
};

#endif /* saturation_hpp */
