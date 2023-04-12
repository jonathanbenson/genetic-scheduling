
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "Config.h"

int main()
{
    // seed the random number generator
    srand(time(0));

    // parse activities and facilitators
    std::pair<std::vector<Activity>, std::vector<std::string>> activitiesAndFacilitators
    = ParseActivitiesAndFacilitators("./config/activities.json");

    std::vector<Activity> activities = activitiesAndFacilitators.first;
    std::vector<std::string> facilitators = activitiesAndFacilitators.second;

    // parse rooms
    std::vector<Room> rooms = ParseRooms("./config/rooms.json");

    // parse times
    std::vector<double> times = ParseTimes("./config/times.json");


    return 0;
}