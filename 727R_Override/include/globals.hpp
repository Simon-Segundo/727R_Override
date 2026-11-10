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

extern pros::Motor grabber;
extern pros::Motor swing;

extern pros::Imu imu;

// extern pros::AIVision AISensor;

extern pros::Distance scoreDistance;

extern pros::Distance leftDistance;
extern pros::Distance rightDistance;
extern pros::Distance backDistance;
extern pros::Distance frontDistance;

extern pros::Rotation cascadeAngle;
extern pros::Rotation swingAngle;

extern pros::adi::DigitalIn swingReset;
extern pros::adi::DigitalIn cascadeReset;

extern lemlib::TrackingWheel vertical_tracking_wheel;
// extern lemlib::TrackingWheel horiz_tracking_wheel;

extern lemlib::Drivetrain drivetrain;
extern lemlib::ControllerSettings lateral_controller;
extern lemlib::ControllerSettings angular_controller;
extern lemlib::OdomSensors sensors;
extern lemlib::Chassis chassis;

extern double swingTrueAngle;
extern double cascadeTrueAngle;
extern volatile bool grabOverride;
extern double robotPosition;