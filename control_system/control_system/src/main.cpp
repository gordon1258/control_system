//
//  main.cpp
//  control_system
//
//  Created by Li-Cheng Hsu on 12/16/19.
//  Copyright © 2019 Li-Cheng Hsu. All rights reserved.
//

#include <iostream>
#include "saturation.hpp"
#include "gtest/gtest.h"


int main(int argc, const char * argv[]) {
     
    saturation* test_sat;
    
    test_sat = new saturation;
    
    std::cout << test_sat->data->isValid << std::endl;
    
    // Google test
    //testing::InitGoogleTest(&argc, argv);
    //return RUN_ALL_TESTS();
    return 0;
}
