
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

class Config
{

public :

    void ParseActivities(const std::string& path);
    void ParseRooms(const std::string& path);
    void ParseTimes(const std::string& path);

    const std::vector<Activity>& GetActivities() const;
    const std::vector<Room>& GetRooms() const;
    const std::vector<double>& GetTimes() const;

private :

    std::vector<Activity> activities;
    std::vector<Room> rooms;
    std::vector<double> times;

};

