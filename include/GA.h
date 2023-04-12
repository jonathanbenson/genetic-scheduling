
#ifndef GA_H
#define GA_H

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

FacilitatorLoadInfo GetFacilitatorLoadInfo(const Schedule& s, int facilitator_id);

bool CoinFlip();

std::vector<double> Softmax(const std::vector<double>& input);

double Fitness(const Schedule& s, const std::vector<Activity>& activities, const std::vector<Room>& rooms, const std::vector<double>& times, const std::vector<std::string>& facilitators);

std::vector<double> GetFitnesses(const std::vector<Schedule>& population, const std::vector<Activity>& activities, const std::vector<Room>& rooms, const std::vector<double>& times, const std::vector<std::string>& facilitators);

std::vector<Schedule> TournamentSelect(const std::vector<Schedule>& population, const std::vector<double>& fitnesses, int n);

std::vector<Schedule> UniformCrossover(const std::vector<Schedule>& parents);

std::vector<Schedule> Mutate(const std::vector<Schedule>& population);

#endif