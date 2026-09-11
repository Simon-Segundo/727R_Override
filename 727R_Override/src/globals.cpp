#include "globals.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "pros/abstract_motor.hpp"

pros::Controller Controller(pros::E_CONTROLLER_MASTER);

pros::MotorGroup left_motors({-11,-12,-13}, pros::MotorGearset::blue);
pros::MotorGroup right_motors({1, 2,3}, pros::MotorGearset::blue);

pros::Motor intakeMotor(-5, pros::MotorGearset::blue);

pros::MotorGroup cascade({-14, 4}, pros::MotorGearset::blue);
pros::MotorGroup grabber({20, -10});

pros::Imu imu(7);

pros::AIVision AISensor(15);

pros::Distance leftDistance(21);
pros::Distance rightDistance(9);
pros::Distance backDistance(6);
pros::Distance frontDistance(7);


pros::Rotation vert_rotation(16);
pros::Rotation horiz_rotation(8);


//NEED NEW DISTANCES AND FLIP THE SENSORS IF NEEDED
lemlib::TrackingWheel vertical_tracking_wheel(&vert_rotation, lemlib::Omniwheel::NEW_2, -0.25);
lemlib::TrackingWheel horiz_tracking_wheel(&horiz_rotation, lemlib::Omniwheel::NEW_2, 1.5);


lemlib::Drivetrain drivetrain(&left_motors, // left motor group
                              &right_motors, // right motor group
                              11.25, // 10 inch track width
                              3.3, // using new 4" omnis
                              450, // drivetrain rpm is 360
                              2 // horizontal drift is 2 (for now)
);

lemlib::ControllerSettings lateral_controller(6, // 6 proportional gain (kP) 7
                                              0, // 0 integral gain (kI)
                                              1.5, // 1 derivative gain (kD) 5 - 3.5
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              10 // maximum acceleration (slew)
);

lemlib::ControllerSettings angular_controller(2.1, // proportional gain (kP) MAKE 1.8 IF DOESNT WORK
                                              0, // integral gain (kI)
                                              11.7, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

lemlib::OdomSensors sensors(&vertical_tracking_wheel, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            &horiz_tracking_wheel, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);

lemlib::Chassis chassis(drivetrain, // drivetrain settings
                        lateral_controller, // lateral PID settings
                        angular_controller, // angular PID settings
                        sensors // odometry sensors
);

// Used for indicating whether the robot's rollers are grabbing an object or not
bool grabbed;

// Used for resetting the robot position using distance sensors
double robotPosition;