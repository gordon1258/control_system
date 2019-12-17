//
//  main.cpp
//  control_system
//
//  Created by Li-Cheng Hsu on 12/16/19.
//  Copyright © 2019 Li-Cheng Hsu. All rights reserved.
//

#include <iostream>
#include "saturation.hpp"

int main(int argc, const char * argv[]) {
    
    
    // Test saturation block
    saturation test_sat;
    
    std:: vector<double> input = {-0.5, 5, 1000, 4, -2, 3, 4, -500};
    double lb = -10, ub = 10;
    
    //test_sat.sat(lb, ub); // no input
    
    test_sat.getInputArray(input);
    test_sat.sat(lb, ub);
    test_sat.printInputArray();
    test_sat.printOutputArray();
    
    return 0;
}
