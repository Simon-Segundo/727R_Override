#include "distanceReset.hpp"
#include "pros/error.h"
#include <iostream>
#include <cmath>
#include <vector>

// Conversion factor from millimeters to inches, as the dist ance sensor reads in MM
constexpr double MM_TO_INCH = 1.0 / 25.4;

// Sensor port definitions (again, adjust these)
#define FRONT_SENSOR_PORT 7
#define BACK_SENSOR_PORT 16
#define LEFT_SENSOR_PORT 4
#define RIGHT_SENSOR_PORT 5

double getAveragedSensorReading(pros::Distance& sensor) {
// Averages the first 10 sensor readings
std::vector<double> validReadings;
validReadings.reserve(NUM_SAMPLES);

std::cout << "[getAveragedSensorReading] Starting readings for sensor on port "
<< sensor.get_port() << "\n";

for (int i = 0; i < NUM_SAMPLES; ++i) { // NUM_SAMPLES is 10 by definition
double reading = sensor.get(); // Reads the distance sensor
std::cout << "[getAveragedSensorReading] Reading " << i << ": " << reading << " mm\n";

// Check for valid sensor reading
if (reading != PROS_ERR_F && reading > 0 && reading <= MAX_VALID_DISTANCE_MM) {
validReadings.push_back(reading);
} else {
std::cout << "[getAveragedSensorReading] Invalid reading encountered: " << reading << "\n";
}

// Small delay between readings to allow sensor to stabilize
pros::delay(10);
}

if (validReadings.empty()) {
std::cout << "[getAveragedSensorReading] No valid readings collected.\n";
return PROS_ERR_F;
}

// Calculate average of valid readings
double sum = 0.0;
for (const auto& val : validReadings) {
sum += val;
}
double average = sum / validReadings.size();

std::cout << "[getAveragedSensorReading] Valid readings count: " << validReadings.size()
<< ", Average: " << average << " mm\n";

return average;
}

void resetRobotPos(pros::Distance& sensor, const WallAxis wallAxisDirection) {
double distance_mm = getAveragedSensorReading(sensor); // Get average distance
if (distance_mm == PROS_ERR_F) { // Check for valid averaged sensor reading
std::cout << "[resetRobotPos] Invalid averaged reading. Aborting position reset.\n";
return;
}

double distance_in = distance_mm * MM_TO_INCH; // Convert mm to inches
std::cout << "[resetRobotPos] Distance in inches (raw): " << distance_in << "\n";

double wallPosition = 0.0;
double sensorOffset = 0.0;
std::string axis;

// Determine wall position and axis
if (wallAxisDirection == WallAxis::POS_X) {
wallPosition = WALL_X_MAX; // +71 inches
axis = "x";
} else if (wallAxisDirection == WallAxis::NEG_X) {
wallPosition = WALL_X_MIN; // -71 inches
axis = "x";
} else if (wallAxisDirection == WallAxis::POS_Y) {
wallPosition = WALL_Y_MAX; // +71 inches
axis = "y";
} else if (wallAxisDirection == WallAxis::NEG_Y) {
wallPosition = WALL_Y_MIN; // -71 inches
axis = "y";
} else {
std::cout << "[resetRobotPos] Invalid wallAxisDirection." "\n";
return;
}

// double trueVal = 0.0;
// double rad = fabs(chassis.getPose().theta) * M_PI / 180;

// if ((axis == "x") && (fabs(chassis.getPose().theta) != 90) || (fabs(chassis.getPose().theta) != 270)) {
//     trueVal = distance_in * cos(rad);
// } else if ((axis == "x") && (fabs(chassis.getPose().theta) == 90) || (fabs(chassis.getPose().theta) == 270)) {
//     trueVal = distance_in;
// } else if ((axis == "y") && (fabs(chassis.getPose().theta) != 0) || (fabs(chassis.getPose().theta) != 180)) {
//     trueVal = distance_in * sin(rad);
// } else if ((axis == "y") && (fabs(chassis.getPose().theta) == 0) || (fabs(chassis.getPose().theta) == 180)) {
//     trueVal = distance_in;
// }


// Determine the sensor offset based on the sensor used
if (sensor.get_port() == FRONT_SENSOR_PORT) {
sensorOffset = FRONT_SENSOR_OFFSET;
} else if (sensor.get_port() == BACK_SENSOR_PORT) {
sensorOffset = BACK_SENSOR_OFFSET;
} else if (sensor.get_port() == LEFT_SENSOR_PORT) {
sensorOffset = LEFT_SENSOR_OFFSET;
} else if (sensor.get_port() == RIGHT_SENSOR_PORT) {
sensorOffset = RIGHT_SENSOR_OFFSET;
} else {
std::cout << "[resetRobotPos] Unknown sensor port: " << sensor.get_port() << "\n";
return;
}

std::cout << "[resetRobotPos] Wall position: " << wallPosition
<< ", Sensor offset: " << sensorOffset << ", Axis: " << axis << "\n";

// CHANGED distance_in TO TRUE VAL **************************
// For positive walls (wallPosition > 0), we need to subtract distances
if (wallPosition > 0) {
    robotPosition = wallPosition - distance_in - sensorOffset;
} else if (wallPosition < 0){
    // For negative walls (wallPosition < 0), we need to add distances which are positive
    robotPosition = wallPosition + distance_in + sensorOffset;
}

std::cout << "[resetRobotPos] Calculated robot position along " << axis << ": " << robotPosition << "\n";

// Get the current pose
lemlib::Pose currentPose = chassis.getPose();
std::cout << "[resetRobotPos] Current Pose: x=" << currentPose.x
<< ", y=" << currentPose.y
<< ", theta=" << currentPose.theta << "\n";

// Update the robot's position along the specified axis
if (axis == "x") {
chassis.setPose(robotPosition, currentPose.y, currentPose.theta);
} else if (axis == "y") {
chassis.setPose(currentPose.x, robotPosition, currentPose.theta);
}

lemlib::Pose newPose = chassis.getPose();
std::cout << "[resetRobotPos] Updated Pose: x=" << newPose.x
<< ", y=" << newPose.y
<< ", theta=" << newPose.theta << "\n";
}