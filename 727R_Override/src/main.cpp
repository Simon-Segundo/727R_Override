#include "autons.h"
#include "globals.hpp"
#include "pros/screen.h"
#include "pros/screen.hpp"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

void lift() {
    if (Controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
        cascade.move_velocity(400);
    } else if (Controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
        cascade.move_velocity(-4600);
    } else {
        cascade.brake();
    }
}

void intake() {
    if (Controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)) {
        intakeMotor.move_velocity(600);
    } else if (Controller.get_digital(pros::E_CONTROLLER_DIGITAL_B)) {
        intakeMotor.move_velocity(-600);
    } else {
        intakeMotor.brake();
    }
}

void grab() {
    if ((Controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)) && (grabbed == false)) {
        grabber.move_velocity(600);
        grabbed = true;
        pros::delay(250);
    } else if ((Controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)) && (grabbed == true)) {
        grabber.move_velocity(600);
        grabbed = false;
        pros::delay(250);
    } else {
        grabber.brake();
    }
}

void initialize() {
	pros::lcd::initialize(); // initialize brain screen
	imu.reset();
    initAISensor();
    chassis.calibrate(); // calibrate sensors
    pros::c::motor_set_voltage_limit(12, 8000);
    pros::c::motor_set_voltage_limit(2, 8000);
    pros::c::motor_set_voltage_limit(5, 8000);
    pros::c::motor_set_voltage_limit(10, 8000);
    pros::c::motor_set_voltage_limit(20, 8000);
	left_motors.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	right_motors.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    cascade.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    // swing.set_brake_mode(hold)
    grabber.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

    // Constantly prints the x, y, and theta values of the robot according to its initial position
    // pros::Task screen_task([&]() {
    //     while (true) {
    //         // print robot location to the brain screen
    //         pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
    //         pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
    //         pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading

	// 		pros::lcd::print(3, "Vertical Encoder: %i", vert_rotation.get_position());
    //    		// print measurements from the rotation sensor

    //         // delay to save resources
    //         pros::delay(20);
    //     }
    // });
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
    while(true) {
        auto goals = scanGoals();
        auto gameObjects = scanGameObjects();

        pros::screen::print(pros::E_TEXT_MEDIUM, 1, "Goals found: %d", goals.size());
        pros::screen::print(pros::E_TEXT_MEDIUM, 2, "Objects found: %d", gameObjects.size());

        pros::delay(50);
    }
    // matchAutoLeft();
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

	while (true) {
        // if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)){
        //     startTime  = pros::millis();
        // }
		// Arcade Control
		int throttle = Controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);    // Gets amount forward/backward from left joystick
		int turn = Controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);  // Gets the turn left/right from right joystick
		chassis.arcade(throttle, turn);                    // Sets drivetrain velocity

        grab();
        lift();
        intake();

		pros::delay(20);                               // Run for 20 ms then update
	}
}