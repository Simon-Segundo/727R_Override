#include "autons.h"
#include "distanceReset.hpp"

void matchAutoLeft() {
    resetRobotPos(backDistance, WallAxis::POS_Y);
    resetRobotPos(rightDistance, WallAxis::NEG_X);
    chassis.moveToPoint(-48,24, 1000, {}, false);
    grabber.move_velocity(-600);
    pros::delay(200);
}