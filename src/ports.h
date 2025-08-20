#pragma once

#include "lemlib/chassis/chassis.hpp"
#include "lemlib/chassis/trackingWheel.hpp"
#include "pros/imu.hpp"
#include "pros/motor_group.hpp"

// drivetrain motors
extern pros::MotorGroup left_motors;
extern pros::MotorGroup right_motors;

// drivetrain object
extern lemlib::Drivetrain drivetrain;

// V5 inertial sensor
extern pros::Imu imu;

// rotational sensors for tracking wheels
extern pros::Rotation left_vertical;
extern pros::Rotation right_vertical;
extern pros::Rotation horizontal;

// tracking wheel objects
extern lemlib::TrackingWheel left_vertical_wheel;
extern lemlib::TrackingWheel right_vertical_wheel;
extern lemlib::TrackingWheel horizontal_wheel;

// odometry sensor object
extern lemlib::OdomSensors odom_sensors;

// PID controller objects
extern lemlib::ControllerSettings lateral_controller;
extern lemlib::ControllerSettings angular_controller;

// chassis object
extern lemlib::Chassis chassis;

// other motor objects

