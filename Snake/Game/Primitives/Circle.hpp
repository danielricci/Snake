#pragma once

#include <Eigen/Dense>

class Circle {
public:
    Circle(int x, int y, int radius) {
        this->positionVector.x() = x;
        this->positionVector.y() = y;
        this->radius = radius;
    }
private:
    Eigen::Vector2f positionVector(0, 0);
    int radius = 0;
};
