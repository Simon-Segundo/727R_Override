#include "autons.h"
// #include "distanceReset.hpp"
#include "globals.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "pros/distance.hpp"

void autoScore () {
    grabber.move_velocity(600);
    cascade.move_velocity(600);
    while(scoreDistance.get_distance() < 200) {
        pros::delay(10);
    }
    pros::delay(700);
    cascade.brake();
    while(swingTrueAngle < 70) {
        swing.move_velocity(600);
    }
    swing.brake();
    left_motors.move_velocity(600);
    right_motors.move_velocity(600);
    pros::delay(50);
    grabber.move_velocity(-600);
    left_motors.brake();
    right_motors.brake();
    pros::delay(400);
    grabber.brake();
    cascade.move_velocity(600);
    pros::delay(500);
    cascade.brake();
}

void cascadeDown() {
    while(!swingReset.get_value()) {
        swing.move_velocity(-600);
        pros::delay(10);
    }
    pros::delay(100);
    swing.brake();
    swingAngle.reset_position();
    swingTrueAngle = swingAngle.get_position()/200.0;
    while(!cascadeReset.get_value()) {
        cascade.move_velocity(-600);
    }
    pros::delay(100);
    cascade.brake();
}

void swingUp() {
    while(swingTrueAngle < 70) {
        swing.move_velocity(600);
        pros::delay(10);
    }
    swing.brake();
}

void swingDown() {
    while(!swingReset.get_value()) {
        swing.move_velocity(-600);
        pros::delay(10);
    }
    pros::delay(100);
    swing.brake();
}

void skillsAuto() {
    // Score Pre-Load
    resetRobotPos(frontDistance, WallAxis::NEG_Y);
    resetRobotPos(rightDistance, WallAxis::NEG_X);
    // chassis.swingToPoint(-24, 48, lemlib::DriveSide::LEFT, 1000, {.forwards = false});
    chassis.moveToPoint(-60, -48, 1000, {.forwards = false});
    resetRobotPos(frontDistance, WallAxis::NEG_X);
    resetRobotPos(rightDistance, WallAxis::NEG_Y);
    chassis.turnToPoint(-40, -48, 1000, {.forwards = false});
    chassis.moveToPoint(-40, -48, 1000, {.forwards = false});
    swingUp();
    intakeMotor.move_velocity(-600);
    cascade.move_velocity(600);
    // From Match Loader to Neutral Goal 4 times
    for (int i; i < 4; i++) {
        // To Match Loader
        chassis.moveToPoint(-60, -48, 1000, {.forwards = false}, false);
        cascadeDown();
        resetRobotPos(frontDistance, WallAxis::NEG_X);
        resetRobotPos(rightDistance, WallAxis::NEG_Y);
        chassis.turnToPoint(-60, -72, 1000);
        // At Match Loader
        intakeMotor.move_velocity(600);
        // Adjust this timeout to affect how long the robot stays at the Match Loader
        chassis.moveToPoint(-60, -60, 3000);
        // To Neutral Goal
        chassis.moveToPoint(-60, -48, 1000);
        chassis.turnToPoint(-40, -48, 1000, {.forwards = false});
        chassis.moveToPoint(-40, -48, 1000, {.forwards = false}, false);
        // At Neutral Goal
        autoScore();
    }
    
}