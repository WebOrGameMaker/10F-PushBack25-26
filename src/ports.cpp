#include "ports.h"
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/chassis/trackingWheel.hpp"
#include "pros/abstract_motor.hpp"
#include "pros/imu.hpp"
#include "pros/motor_group.hpp"

// drivetrain motors
pros::MotorGroup left_motors({-1, 2, -3}, pros::MotorGearset::blue);
pros::MotorGroup right_motors({4, -5, 6}, pros::MotorGearset::blue);

// instantiating drivetrain object with previous motors and other measurements
lemlib::Drivetrain drivetrain(&left_motors, // left motors
                              &right_motors, // right motors
                              11.624, // track width (inches) from center of one wheel to the other
                              lemlib::Omniwheel::NEW_325, // 3.25 inch omnis
                              450, // drivetrain rpm 450
                              2 // 2 for now
);

// V5 inertial sensor
pros::Imu imu(10);

// rotational sensors for tracking wheels
pros::Rotation left_vertical(-7); // offset -2.248 in
pros::Rotation right_vertical(8); // offset 2.333 in
pros::Rotation horizontal(-9);  // offset -4.243 in

// instantiating tracking wheel objects with previous sensors, wheel diameters, and offsets
// for vertical tracking wheels: negative = left, positive = right
// for horizontal tracking wheels: negative = backwards, positive = forwards
lemlib::TrackingWheel left_vertical_wheel(&left_vertical, 2.00, -2.248);
lemlib::TrackingWheel right_vertical_wheel(&right_vertical, 2.00, -2.333);
lemlib::TrackingWheel horizontal_wheel(&horizontal, 2.00, -4.243);

// instantiating odometery sensor object with tracking wheels and inertial sensor
lemlib::OdomSensors odom_sensors(&left_vertical_wheel, // left vertical tracking wheel
                                 &right_vertical_wheel, // right vertical tracking wheel
                                 &horizontal_wheel, // horizontal tracking wheel
                                 nullptr,
                                 &imu // inertial sensor
);

// these two PID objects are temporary, will tune later
// lateral PID controller
lemlib::ControllerSettings lateral_controller(10, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              3, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              20 // maximum acceleration (slew)
);

// angular PID controller
lemlib::ControllerSettings angular_controller(2, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              10, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in degrees
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in degrees
                                              500, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

lemlib::Chassis chassis(drivetrain, // drivetrain settings
        lateral_controller, // lateral PID controller
       angular_controller, // angular PID controller
               odom_sensors); // odometry sensors

// rest of the motors on the robot

