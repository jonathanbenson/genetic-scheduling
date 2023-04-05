
#include "Config.h"

std::vector<Activity> Config::ParseActivities(const std::string& path) const
{
    return std::vector<Activity>();
}

std::vector<Room> Config::ParseRooms(const std::string& path) const
{
    return std::vector<Room>();
}

std::vector<double> Config::ParseTimes(const std::string& path) const
{
    return std::vector<double>();
}

const std::vector<Activity>& Config::GetActivities() const
{
    return activities;
}

const std::vector<Room>& Config::GetRooms() const
{
    return rooms;
}

const std::vector<double>& Config::GetTimes() const
{
    return times;
}
