#include "aiVision.hpp"
#include "globals.hpp"
#include "pros/ai_vision.hpp"

void initAISensor() {
    // AISensor.reset();

    // // Allows the AI vision sensor to detect colors, objects, and april tags
    // AISensor.enable_detection_types(
    //     pros::AivisionModeType::colors,
    //     pros::AivisionModeType::objects,
    //     pros::AivisionModeType::tags
    // );

    // Assigns rgb values to color ids
    pros::AIVision::Color redColor = {
        .id = 1,
        .red = 220,
        .green = 40,
        .blue = 40,
        .hue_range = 20,
        .saturation_range = 0.5
    };
    pros::AIVision::Color blueColor = {
        .id = 2,
        .red = 40,
        .green = 90,
        .blue = 220,
        .hue_range = 20,
        .saturation_range = 0.5
    };

//     AISensor.set_color(redColor);
//     AISensor.set_color(blueColor);

//     AISensor.set_tag_family(pros::AivisionTagFamily::tag_16H5);
// }

// std::vector<identifiedGoal> scanGoals() {
//     std::vector<identifiedGoal> goals;
//     auto objects = AISensor.get_all_objects();

//     // First pass: collect tag centers
//     for (auto &tagObj : objects) {
//         if (!pros::AIVision::is_type(tagObj, pros::AivisionDetectType::tag)) continue;

//         int tagX = (tagObj.object.tag.x0 + tagObj.object.tag.x1 +
//                     tagObj.object.tag.x2 + tagObj.object.tag.x3) / 4;
//         int tagY = (tagObj.object.tag.y0 + tagObj.object.tag.y1 +
//                     tagObj.object.tag.y2 + tagObj.object.tag.y3) / 4;

//         bool foundColor = false;
//         bool goalIsRed = false;

//         // Second pass: find nearest color blob to this tag
//         int bestDist = INT32_MAX;
//         for (auto &colorObj : objects) {
//             if (!pros::AIVision::is_type(colorObj, pros::AivisionDetectType::color)) continue;

//             int cx = colorObj.object.color.xoffset + colorObj.object.color.width / 2;
//             int cy = colorObj.object.color.yoffset + colorObj.object.color.height / 2;
//             int dist = std::abs(cx - tagX) + std::abs(cy - tagY);

//             if (dist < bestDist && dist < 40) { // 40px threshold, tune this
//                 bestDist = dist;
//                 goalIsRed = (colorObj.id == 2);
//                 foundColor = true;
//             }
//         }

//         if (foundColor) {
//             goals.push_back(identifiedGoal{
//                 .tag_id = tagObj.id,
//                 .is_red = goalIsRed,
//                 .x = tagX,
//                 .y = tagY
//             });
//         }
//     }
//     return goals;
// }

// std::vector<identifiedGameObject> scanGameObjects() {
//     std::vector<identifiedGameObject> found;
//     auto objects = AISensor.get_all_objects();

//     for (auto &object : objects) {
//         if (!pros::AIVision::is_type(object, pros::AivisionDetectType::object)) continue;

//         found.push_back(identifiedGameObject{
//             .type = static_cast<gameObjectID>(object.id),
//             .x = object.object.element.xoffset + object.object.element.width / 2,
//             .y = object.object.element.yoffset + object.object.element.height / 2,
//             .score = object.object.element.score
//         });
//     }
//     return found;
}