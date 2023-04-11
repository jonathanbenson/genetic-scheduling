
#include <nlohmann/json.hpp>
#include <fstream>

#include "Config.h"

using json = nlohmann::json;
using ifstream = std::ifstream;
using json_arr_iter = nlohmann::json_abi_v3_11_2::detail::iter_impl<nlohmann::json_abi_v3_11_2::json>;

std::pair<std::vector<Activity>, std::vector<std::string>> ParseActivitiesAndFacilitators(const std::string& path)
{
    /*
    Parses activities into the Activity model.

    Also outputs a list of facilitators (only distinct facilitators derived from each activity's preferred and other facilitators)
    */

    ifstream in(path);

    json j;

    in >> j;

    std::vector<Activity> activities;
    std::vector<std::string> facilitators;

    for (json_arr_iter iter = j.begin(); iter != j.end(); ++iter)
    {
        json actJson = *iter;

        // parse activity
        Activity act;
        act.Name = actJson["name"].get<std::string>();
        act.Section = actJson["section"].get<std::string>();
        act.ExpectedEnrollment = actJson["expected_enrollment"].get<size_t>();
        act.PreferredFacilitators = actJson["preferred_facilitators"].get<std::vector<std::string>>();
        act.OtherFacilitators = actJson["other_facilitators"].get<std::vector<std::string>>();

        activities.push_back(act);

        // parse facilitators
        for (std::vector<std::string>::iterator jter = act.PreferredFacilitators.begin(); jter != act.PreferredFacilitators.end(); jter++)
            if (std::find(facilitators.begin(), facilitators.end(), *jter) == facilitators.end())
                facilitators.push_back(*jter);

        for (std::vector<std::string>::iterator jter = act.OtherFacilitators.begin(); jter != act.OtherFacilitators.end(); jter++)
            if (std::find(facilitators.begin(), facilitators.end(), *jter) == facilitators.end())
                facilitators.push_back(*jter);

    }

    in.close();

    return std::pair<std::vector<Activity>, std::vector<std::string>>(activities, facilitators);
}

std::vector<Room> ParseRooms(const std::string& path)
{
    /*
    Parses rooms into the Room model
    
    */
    ifstream in(path);

    json j;

    in >> j;

    std::vector<Room> rooms;

    for (json_arr_iter iter = j.begin(); iter != j.end(); ++iter)
    {
        json roomJson = *iter;

        Room room;
        room.Name = roomJson["name"].get<std::string>();
        room.Number = roomJson["number"].get<size_t>();
        room.Capacity = roomJson["capacity"].get<size_t>();

        rooms.push_back(room);
    }

    in.close();

    return rooms;
}

std::vector<double> ParseTimes(const std::string& path)
{
    /*
    Parses times into a list of doubles
    */

    ifstream in(path);

    json j;

    in >> j;

    std::vector<double> times;

    for (json_arr_iter iter = j.begin(); iter != j.end(); ++iter)
        times.push_back(*iter);

    in.close();

    return times;
}

