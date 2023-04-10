
#include <iostream>
#include <vector>
#include <string>

struct Activity
{
    std::string Name;
    uint ExpectedEnrollment;
    std::vector<std::string> PreferredFacilitators;
    std::vector<std::string> OtherFacilitators;
};

struct Room
{
    std::string Name;
    uint Capacity;
};

std::vector<Activity> ParseActivities(const std::string& path);
std::vector<Room> ParseRooms(const std::string& path);
std::vector<double> ParseTimes(const std::string& path);

