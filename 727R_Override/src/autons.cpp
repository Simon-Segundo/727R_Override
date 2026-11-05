#include "autons.h"
// #include "distanceReset.hpp"
#include "globals.hpp"
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

void swingUp() {
    while(swingTrueAngle < 70) {
        swing.move_velocity(600);
        pros::delay(10);
    }
    swing.brake();
}

void swingDown() {
    while(!swingResetter.get_value()) {
        swing.move_velocity(-600);
        pros::delay(10);
    }
    pros::delay(100);
    swing.brake();
}

void skillsAuto() {
    // resetRobotPos(frontDistance, WallAxis::NEG_Y);
    // resetRobotPos(rightDistance, WallAxis::NEG_X);
    // chassis.moveToPoint(-24, 24, 1000, {}, false);
    // swingUp();
    // intakeMotor.move_velocity(-600);
    // chassis.moveToPoint(-36, 36, 1000, {.forwards = false});
    autoScore();
}