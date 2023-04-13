
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

double AverageFitness(const std::vector<double>& v);

bool CoinFlip(double threshold = .5);

int RandomIndex(int n);

double AverageOfLastNValues(const std::vector<double>& vec, int n);

std::vector<double> Softmax(const std::vector<double>& input);

double Fitness(const Schedule& s, const std::vector<Activity>& activities, const std::vector<Room>& rooms, const std::vector<double>& times, const std::vector<std::string>& facilitators);

std::vector<double> GetFitnesses(const std::vector<Schedule>& population, const std::vector<Activity>& activities, const std::vector<Room>& rooms, const std::vector<double>& times, const std::vector<std::string>& facilitators);

std::vector<Schedule> InitPopulation(int numActivities, int numRooms, int numTimes, int numFacilitators, int n);

std::vector<Schedule> TournamentSelect(const std::vector<Schedule>& population, const std::vector<double>& fitnesses, int k);

std::vector<Schedule> PointCrossover(const std::vector<Schedule>& parents);

std::vector<Schedule> Mutate(const std::vector<Schedule>& population, int numRooms, int numTimes, int numFacilitators, double mutationRate);

#endif