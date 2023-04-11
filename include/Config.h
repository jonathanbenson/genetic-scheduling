
#ifndef CONFIG_H
#define CONFIG_H

#include <iostream>
#include <vector>
#include <string>

struct Activity
{
    std::string Name;
    std::string Section;
    size_t ExpectedEnrollment;
    std::vector<std::string> PreferredFacilitators;
    std::vector<std::string> OtherFacilitators;
};

struct Room
{
    std::string Name;
    size_t Number;
    size_t Capacity;
};

std::pair<std::vector<Activity>, std::vector<std::string>>
ParseActivitiesAndFacilitators(const std::string& path);

std::vector<Room> ParseRooms(const std::string& path);
std::vector<double> ParseTimes(const std::string& path);

#endif