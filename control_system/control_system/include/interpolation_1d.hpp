//
//  interpolation_1d.hpp
//  control_system
//
//  Created by Li-Cheng Hsu on 12/22/19.
//  Copyright © 2019 Li-Cheng Hsu. All rights reserved.
//

#ifndef interpolation_1d_hpp
#define interpolation_1d_hpp

#include <stdio.h>
#include <vector>

// 1D Inpterpolatio
// - Out-of-range handling: Clamp

class interpolation_1d
{
public:
    struct output
    {
        bool isValid;
        double y;
        
        output() : y(0), isValid(false) {};
        ~output() {y = 0; isValid = false;};
    };
    
    output data;
    interpolation_1d() : X(NULL), Y(NULL) {};
    interpolation_1d(std::vector<double> X_table ,std::vector<double> Y_table) : X(X_table), Y(Y_table) {};
    ~interpolation_1d() {X.clear(); Y.clear();};
    
    void setX(std::vector<double> X_table);
    void setY(std::vector<double> Y_table);
    void intrp_1d(double x);
    output getOutput() const;
    
private:
    std::vector<double> X;
    std::vector<double> Y;
    
    bool checkValidity();
    bool checkXOrder();
};
#endif /* interpolation_1d_hpp */
