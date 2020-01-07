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
#include "gnuplot-iostream.h"


#include <map>
#include <vector>
#include <cmath>
#include <boost/tuple/tuple.hpp>
#include <Eigen/Dense>

int main(int argc, const char * argv[]) {
    
    /*
    // Test gnuplot
    //Gnuplot gp;
    
    //gp << "plot cos(x))\n";
    Gnuplot gp;

    // Gnuplot vectors (i.e. arrows) require four columns: (x,y,dx,dy)

    // You can also use a separate container for each column, like so:
    int n = 1000;
    std::vector<std::pair<double,double>> X_t;
    std::vector<std::pair<double,double>> Y_t;
    
    std::vector<double> t;
    std::vector<double> x(n, 500);
    std::vector<double> y;

    // Make the data
    double dt = 0.01;
    
    for(int i = 0; i < n; ++i)
    {
        t.push_back(i * dt);
        y.push_back(i);
        X_t.push_back(std::make_pair(t[i], x[i]));
        Y_t.push_back(std::make_pair(t[i], y[i]));
    }
    
    
    
    // Don't forget to put "\n"  or std::endl at the end of each line!
    //gp << "set xrange [-2:2]\nset yrange [-2:2]\n";
    // '-' means read from stdin.  The send1d() function sends data to
    // gnuplot's stdin.

    // Plot 1
    gp << "set xrange [0:10]\n";
    gp << "plot '-' with lines title 'testing restuls', '-' with lines title 'testing results 2'"<<std::endl;
    gp.send1d(boost::make_tuple(t,x));
    gp.send1d(boost::make_tuple(t,y));
    
    // Plot 2
    gp << "plot" << gp.file1d(X_t) << "with lines title 'X_t',"
    << gp.file1d(Y_t) << "with lines title 'Y_t'" << std::endl;
    */
    
    // Test eigen: Matrices and vectors
    //Eigen::MatrixXd  m = Eigen::MatrixXd::Random(3, 3);
    //m = (m + Eigen::MatrixXd::Constant(3, 3, 1.2)) * 50;
    Eigen::VectorXd v(2);
    v(0) = 1;
    v(1) = 2;
    
    std::cout << "v =\n" << v << std::endl;
    
    Eigen::MatrixXd m(2,2);
    Eigen::Matrix2d m2;
    /*
    m(0,0) = 1;
    m(1,0) = 0;
    m(0,1) = 0;
    m(1,1) = 1;
    */
    m << 1, 0,
         0, 1;
    m2 << 1, 2,
          3, 4;
    
    std::cout << "m2 * m =\n" << m2 * m<< std::endl;
    
    
    return 0;
}
