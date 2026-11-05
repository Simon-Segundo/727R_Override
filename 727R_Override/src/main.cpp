#include "autons.h"
#include "globals.hpp"
#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/motors.hpp"
#include "pros/rtos.hpp"
#include "pros/screen.h" // IWYU pragma: keep
#include "pros/screen.hpp" // IWYU pragma: keep

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

 // Automatically scores a cup and pin when activated

void lift() {
    // if (Controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
    //     cascade.move_velocity(600);
    // } else if (Controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
    //     cascade.move_velocity(-600);
    // } else {
    //     cascade.brake();
    // }

    if (Controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
        grabOverride = true;
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
        pros::delay(100);
        grabber.move_velocity(-600);
        pros::delay(400);
        grabber.brake();
        cascade.move_velocity(600);
        pros::delay(500);
        cascade.brake();
    } else if (Controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
        while(!swingResetter.get_value()) {
            swing.move_velocity(-600);
            pros::delay(10);
        }
        pros::delay(100);
        swing.brake();
        swingAngle.reset_position();
        swingTrueAngle = swingAngle.get_position()/200.0;
        cascade.move_velocity(-600);
    } else if (Controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)) {
        cascade.move_velocity(600);
    } else {
        cascade.brake();
        grabOverride = false;
    }
}

void intake() {
    if (Controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
        grabOverride = false;
        intakeMotor.move_velocity(600);
        grabber.move_velocity(600);
    } else if (Controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
        grabOverride = false;
        intakeMotor.move_velocity(-600);
        grabber.move_velocity(-600);
    } else {
        intakeMotor.brake();
        if(!grabOverride) {
            grabber.brake();
        }
    }
}

void swingGrab() {
    if ((Controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) && (swingTrueAngle < 80)) {
        while(swingTrueAngle < 90) {
            swing.move_velocity(600);
            pros::delay(10);
        }
        swing.brake();
    } else if ((Controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) && (swingTrueAngle > 80)) {
        while(!swingResetter.get_value()) {
            swing.move_velocity(-600);
            pros::delay(10);
        }
        swing.brake();
    }
    // if (Controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
    //     swing.move_velocity(600);
    // } else if (Controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
    //     swing.move_velocity(-600);
    // } else {
    //     swing.brake();
    // }
}

void initialize() {
	pros::lcd::initialize(); // initialize brain screen
    swingAngle.reset();
    swingAngle.set_position(0);
    cascadeAngle.reset();
    cascadeAngle.set_position(0);
    swingTrueAngle = 0;
    cascadeTrueAngle = 0;
    initAISensor();
    chassis.calibrate(); // calibrate sensors
    // pros::c::motor_set_voltage_limit(11, 8000);
    // pros::c::motor_set_voltage_limit(12, 8000);
    cascade.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    swing.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    grabber.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

    left_motors.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    right_motors.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

    // Constantly prints the x, y, theta, vertical encoder, and rotation sensor values of the robot
    pros::Task screen([]() {
        int count = 0;
        while (true) {
            if (swingResetter.get_value()) {
                swingAngle.set_position(0);
            }
            // if (cascadeResetter.get_value()) {
            //     cascadeAngle.set_position(0);
            // }
            swingTrueAngle = swingAngle.get_position()/200.0;
            cascadeTrueAngle = cascadeAngle.get_position()/60.0;
            // pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
            // pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
            // pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
            
            pros::lcd::print(3, "Cascade Angle: %f", cascadeTrueAngle);
            pros::lcd::print(4, "Swing Angle: %f", swingTrueAngle);
            // pros::lcd::print(5, "Ticks: %d", count++);

            pros::delay(50);
        }
    });
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
 
void autonomous() {
	left_motors.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	right_motors.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);

    // while(true) {
    //     auto goals = scanGoals();
    //     auto gameObjects = scanGameObjects();

    //     pros::screen::print(pros::E_TEXT_MEDIUM, 1, "Goals found: %d", goals.size());
    //     pros::screen::print(pros::E_TEXT_MEDIUM, 2, "Objects found: %d", gameObjects.size());

    //     pros::delay(50);
    // }

    // matchAutoLeft();
    skillsAuto();
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
    pros::Task swingTask ([&] (){
        while(true) {
            swingGrab();
        
            pros::delay(10);
        }
    });
    pros::Task liftTask ([] () {
        while(true) {
            lift();

            pros::delay(10);
        }
    });

	while (true) {
        // if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)){
        //     startTime  = pros::millis();
        // }
		// Arcade Control
		int throttle = Controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);    // Gets amount forward/backward from left joystick
		int turn = Controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);  // Gets the turn left/right from right joystick
		chassis.arcade(throttle, turn);                    // Sets drivetrain velocity

        intake();

		pros::delay(20);                               // Run for 20 ms then update
	}
}