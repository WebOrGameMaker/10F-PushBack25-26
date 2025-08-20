#include "pros/llemu.hpp"
#include "ports.cpp"

void print_tracking_wheels() {
    pros::lcd::print(3, "Left Vertical: %f", left_vertical_wheel.getOffset());
    pros::lcd::print(4, "Right Vertical: %f", right_vertical_wheel.getOffset());
    pros::lcd::print(5, "Horizontal: %f", horizontal_wheel.getOffset());
}