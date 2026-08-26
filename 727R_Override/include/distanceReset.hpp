#ifndef DISTANCE_RESET_HPP //Defines the file
#define DISTANCE_RESET_HPP
#include "globals.hpp" // IWYU pragma: keep
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "pros/distance.hpp"
#include <string> // IWYU pragma: keep

// added an enum class so you don’t have to type out strings -davis
enum class WallAxis {
    POS_X,
    POS_Y,
    NEG_X,
    NEG_Y
};

// Field dimensions (in inches)
constexpr double FIELD_SIZE = 142.0; // Field spans from -72 to +72 inches
// Wall coordinates
constexpr double WALL_X_MIN = -71.0; // Negative X wall at X = -71 inches
constexpr double WALL_X_MAX = 71.0; // Positive X wall at X = +71 inches
constexpr double WALL_Y_MIN = -71.0; // Negative Y wall at Y = -71 inches
constexpr double WALL_Y_MAX = 71.0; // Positive Y wall at Y = +71 inches
// Sensor offsets from the robot's center along each axis (in inches)
constexpr double FRONT_SENSOR_OFFSET = 7.5;
constexpr double BACK_SENSOR_OFFSET = 6.75;
constexpr double RIGHT_SENSOR_OFFSET = 4.25;
constexpr double LEFT_SENSOR_OFFSET = 4.25;
// Filtering constants
constexpr int NUM_SAMPLES = 6; // Averages 6 values of the distance sensor
constexpr double MAX_VALID_DISTANCE_MM = 3000.0; // Maximum valid distance in mm

void resetRobotPos(pros::Distance& sensor, const WallAxis wallAxisDirection); //The reset function

double getAveragedSensorReading(pros::Distance& sensor); //The average function
#endif // DISTANCE_RESET_HPP