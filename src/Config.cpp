
#include <nlohmann/json.hpp>
#include <fstream>

#include "Config.h"

using json = nlohmann::json;
using ifstream = std::ifstream;
using json_arr_iter = nlohmann::json_abi_v3_11_2::detail::iter_impl<nlohmann::json_abi_v3_11_2::json>;

void Config::ParseActivities(const std::string& path)
{
    ifstream in(path);

    json j;

    in >> j;

    for (json_arr_iter iter = j.begin(); iter != j.end(); ++iter)
    {
        json actJson = *iter;

        Activity act;
        act.Name = actJson["name"].get<std::string>();
        act.ExpectedEnrollment = actJson["expected_enrollment"].get<uint>();
        act.PreferredFacilitators = actJson["preferred_facilitators"].get<std::vector<std::string>>();
        act.OtherFacilitators = actJson["other_facilitators"].get<std::vector<std::string>>();

        activities.push_back(act);
    }

    in.close();
}

void Config::ParseRooms(const std::string& path)
{
    ifstream in(path);

    json j;

    in >> j;

    for (json_arr_iter iter = j.begin(); iter != j.end(); ++iter)
    {
        json roomJson = *iter;

        Room room;
        room.Name = roomJson["name"].get<std::string>();
        room.Capacity = roomJson["capacity"].get<uint>();

        rooms.push_back(room);
    }

    in.close();
}

void Config::ParseTimes(const std::string& path)
{

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
