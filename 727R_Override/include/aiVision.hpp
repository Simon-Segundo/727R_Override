#include "globals.hpp" // IWYU pragma: keep

// Declares the ID of the AprilTag on each goal
enum aprilTagID {
    goal1 = 1,
    goal2 = 2,
    goal3 = 3,
    goal4 = 4
};

// Declares which color the goal is
enum colorID {
    red = 1,
    blue = 2
};

struct identifiedGoal {
    int tag_id;
    bool is_red;
    int x, y;
};

// Declares the name of each game object
enum gameObjectID {
    redYellowPin = 1,
    blueYellowPin = 2,
    yellowYellowPin = 3,
    redBluePin = 4,
    clearCup = 5,
    solidCup = 6
};

struct identifiedGameObject {
    gameObjectID type;
    int x, y, score;
};

// Shared sensor instance - declared here, defined in the .cpp
extern pros::AIVision aivision;

// Function declarations
void initAISensor();
std::vector<identifiedGoal> scanGoals();
std::vector<identifiedGameObject> scanGameObjects();