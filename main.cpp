
#include <iostream>
#include <vector>
#include "Config.h"

int main()
{

    std::vector<Activity> activities = ParseActivities("./config/activities.json");
    std::vector<Room> rooms = ParseRooms("./config/rooms.json");
    std::vector<double> times = ParseTimes("./config/times.json");


    return 0;
}