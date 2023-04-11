
#include "Config.h"
#include <string>

struct Event
{

    size_t RoomIndex;
    size_t ActivityIndex;
    size_t TimeIndex;
    size_t FacilitatorIndex;

};

struct Schedule
{
    std::vector<Event> events;
};

struct FacilitatorLoadInfo
{
    size_t Total;
    size_t NumNonConflicts;
    size_t NumConflicts;
    size_t NumConsecutive;
};

int FacilitatorLoad(const Schedule& s, int facilitatorIndex);

double Fitness(const Schedule& s, const std::vector<Activity>& activities, const std::vector<Room>& rooms, const std::vector<double>& times, const std::vector<std::string>& facilitators);

Schedule TournamentSelect(const std::vector<Schedule>& population, int n);

Schedule Crossover(const Schedule& p, const Schedule& q);

void Mutate(double mutationRate);