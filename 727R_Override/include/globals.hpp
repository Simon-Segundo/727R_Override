#include "pros/distance.hpp"
#include "pros/motors.hpp" // IWYU pragma: keep
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "lemlib/chassis/chassis.hpp" // IWYU pragma: keep
#include "lemlib/chassis/trackingWheel.hpp" // IWYU pragma: keep
#include "pros/abstract_motor.hpp" // IWYU pragma: keep
#include "pros/adi.h" // IWYU pragma: keep
#include "pros/adi.hpp" // IWYU pragma: keep
#include "liblvgl/llemu.hpp" // IWYU pragma: keep
#include "pros/apix.h" // IWYU pragma: keep
#include "pros/colors.hpp" // IWYU pragma: keep
#include "pros/device.hpp" // IWYU pragma: keep
#include "pros/misc.h" // IWYU pragma: keep
#include "pros/misc.hpp" // IWYU pragma: keep
#include "pros/motors.h" // IWYU pragma: keep
#include "pros/optical.h" // IWYU pragma: keep
#include "pros/optical.hpp" // IWYU pragma: keep
#include "pros/misc.h" // IWYU pragma: keep
#include "pros/rtos.hpp" // IWYU pragma: keep
#include <algorithm> // IWYU pragma: keep
#include <cmath> // IWYU pragma: keep
#include <thread> // IWYU pragma: keep
#pragma once

extern pros::Controller Controller;

extern pros::MotorGroup left_motors;
extern pros::MotorGroup right_motors;

extern pros::Motor intakeMotor;

extern pros::MotorGroup cascade;
extern pros::MotorGroup arm;

extern pros::adi::DigitalOut claw;

extern pros::Imu imu;

extern pros::AIVision AIsensor;

extern pros::Optical opti;
extern pros::Distance leftDistance;
extern pros::Distance rightDistance;
extern pros::Distance backDistance;
extern pros::Distance frontDistance;


extern pros::Rotation vert_rotation;
extern pros::Rotation horiz_rotation;


extern lemlib::TrackingWheel vertical_tracking_wheel;

extern lemlib::Drivetrain drivetrain;
extern lemlib::ControllerSettings lateral_controller;
extern lemlib::ControllerSettings angular_controller;
extern lemlib::OdomSensors sensors;
extern lemlib::Chassis chassis;

extern bool clamped;
extern double robotPosition;