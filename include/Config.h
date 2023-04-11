
#include <iostream>
#include <vector>
#include <string>

struct Activity
{
    std::string Name;
    std::string Section;
    uint ExpectedEnrollment;
    std::vector<std::string> PreferredFacilitators;
    std::vector<std::string> OtherFacilitators;
};

struct Room
{
    std::string Name;
    uint Capacity;
};

std::pair<std::vector<Activity>, std::vector<std::string>>
ParseActivitiesAndFacilitators(const std::string& path);

std::vector<Room> ParseRooms(const std::string& path);
std::vector<double> ParseTimes(const std::string& path);

