#pragma once

#include <Eigen/Dense>

class Circle {
public:
    Circle(int x, int y, int radius) {
        this->x = x;
        this->y = y;
        this->radius = radius;
    }
    
    int x = 0;
    int y = 0;
    int radius = 0;
};
