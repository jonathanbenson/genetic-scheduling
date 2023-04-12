
#include <algorithm>
#include <map>
#include <set>
#include <cmath>
#include <random>
#include "GA.h"

double AverageFitness(const std::vector<double>& v) {
  if (v.empty()) return 0.0;
  double sum = 0.0;
  for (double d : v) {
    sum += d;
  }
  return sum / v.size();
}

bool CoinFlip(double threshold) {
  std::random_device rd;  // obtain a random number from hardware
  std::mt19937 gen(rd());  // seed the generator
  std::uniform_real_distribution<> distr(0.0, 1.0);  // define the range
  return distr(gen) < threshold;  // check if the result is below the threshold
}

int RandomIndex(int n) {
  std::random_device rd;  // obtain a random number from hardware
  std::mt19937 gen(rd());  // seed the generator
  std::uniform_int_distribution<> distr(0, n - 1);  // define the range
  return distr(gen);  // generate and return the random integer
}

// Convert a vector of doubles to a probability distribution using softmax algorithm
std::vector<double> Softmax(const std::vector<double>& input) {
    std::vector<double> output;
    double sum = 0.0;

    // Calculate the sum of exponential of each input element
    for (int i = 0; i < input.size(); i++) {
        sum += std::exp(input[i]);
    }

    // Calculate the probability distribution by dividing each exponential by the sum
    for (int i = 0; i < input.size(); i++) {
        output.push_back(std::exp(input[i]) / sum);
    }

    return output;
}





double Fitness(const Schedule& s, const std::vector<Activity>& activities, const std::vector<Room>& rooms, const std::vector<double>& times, const std::vector<std::string>& facilitators)
{
    double fitness = 0;

    // keep track of how many events a facilitator is assigned to, and at what times
    std::vector<std::vector<int>> facilitatorLoads(facilitators.size(), std::vector<int>(times.size(), 0));

    for (Event e : s.events)
    {
        for (Event f : s.events)
        {
            if (e.ActivityIndex != f.ActivityIndex)
            {
                // Activity is scheduled at the same time in the same room as another of the activities: -0.5
                if (e.TimeIndex == f.TimeIndex && e.RoomIndex == f.RoomIndex)
                    fitness -= .5;
            }
        }

        // Activities is in a room with capacity > 6 times expected enrollment: -0.4
        if (rooms.at(e.RoomIndex).Capacity > activities.at(e.ActivityIndex).ExpectedEnrollment * 6)
            fitness -= .4;
        // Activities is in a room with capacity > 3 times expected enrollment: -0.2
        else if (rooms.at(e.RoomIndex).Capacity > activities.at(e.ActivityIndex).ExpectedEnrollment * 3)
            fitness -= .2;
        // Activities is in a room too small for its expected enrollment: -0.5
        else if (rooms.at(e.RoomIndex).Capacity < activities.at(e.ActivityIndex).ExpectedEnrollment)
            fitness -= .5;
        else
            fitness += .3;

        
        
        const std::vector<std::string>& ePrefferedFacilitators = activities.at(e.ActivityIndex).PreferredFacilitators;
        const std::vector<std::string>& eOtherFacilitators = activities.at(e.ActivityIndex).OtherFacilitators;

        // Activities is overseen by a preferred facilitator: + 0.5
        if (std::find(ePrefferedFacilitators.begin(), ePrefferedFacilitators.end(), facilitators.at(e.FacilitatorIndex)) != ePrefferedFacilitators.end())
            fitness += .5;

        // Activities is overseen by another facilitator listed for that activity: +0.2
        else if (std::find(eOtherFacilitators.begin(), eOtherFacilitators.end(), facilitators.at(e.FacilitatorIndex)) != eOtherFacilitators.end())
            fitness += .2;

        // Activities is overseen by some other facilitator: -0.1
        else
            fitness -= .1;

        // keep track of how many events a facilitator is assigned to, and at what times
        facilitatorLoads.at(e.FacilitatorIndex).at(e.TimeIndex)++;

    }

    int facilitatorIndex = 0;

    for (std::vector<int> loads : facilitatorLoads)
    {
        int loadTotal = 0;

        for (int load : loads)
        {
            // Activity facilitator is scheduled for more than one activity at the same time: - 0.2
            if (load > 1)
                fitness -= .2;

            // Activity facilitator is scheduled for only 1 activity in this time slot: + 0.2
            else if (load == 1)
                fitness += .2;
        }

        // Facilitator is scheduled to oversee more than 4 activities total: -0.5
        if (loadTotal > 4)
            fitness -= .5;

        // Facilitator is scheduled to oversee 1 or 2 activities*: -0.4
        //     Exception: Dr. Tyler is committee chair and has other demands on his time. 
        //     *No penalty if he’s only required to oversee < 2 activities.
        else if ((loadTotal == 2 || loadTotal == 1) && facilitators.at(facilitatorIndex) != "Tyler")
            fitness -= .4;

        facilitatorIndex++;
    }

    return fitness;

}

std::vector<double> GetFitnesses(const std::vector<Schedule>& population, const std::vector<Activity>& activities, const std::vector<Room>& rooms, const std::vector<double>& times, const std::vector<std::string>& facilitators)
{
    std::vector<double> fitnesses;

    for (Schedule schedule : population)
        fitnesses.push_back(Fitness(schedule, activities, rooms, times, facilitators));

    return fitnesses;
}

std::vector<Schedule> InitPopulation(int numActivities, int numRooms, int numTimes, int numFacilitators, int n)
{
    std::vector<Schedule> initPopulation;

    for (int i = 0; i < n; ++i)
    {
        Schedule newSchedule;

        for (int j = 0; j < numActivities; ++j)
        {
            Event newEvent;

            newEvent.ActivityIndex = j;
            newEvent.RoomIndex = RandomIndex(numRooms);
            newEvent.TimeIndex = RandomIndex(numTimes);
            newEvent.FacilitatorIndex = RandomIndex(numFacilitators);

            newSchedule.events.push_back(newEvent);
        }

        initPopulation.push_back(newSchedule);
    }

    return initPopulation;
}

std::vector<Schedule> TournamentSelect(const std::vector<Schedule>& population, const std::vector<double>& fitnesses, int k)
{
    // get vector of population indices for later code
    std::vector<int> populationIndices;

    for (int i = 0; i < population.size(); ++i)
        populationIndices.push_back(i);


    std::vector<Schedule> parents;

    for (int i = 0; i < population.size(); ++i)
    {
        // sample n candidates
        std::vector<int> candidateIndices;

        std::sample(
            populationIndices.begin(),
            populationIndices.end(),
            std::back_inserter(candidateIndices),
            k,
            std::mt19937{std::random_device{}()}
        );

        // get candidate with max fitness
        int bestCandidateIndex = candidateIndices.at(0);

        for (int j = 1; j < k; j++)
        {
            int nextCandidateIndex = candidateIndices.at(j);

            if (fitnesses.at(nextCandidateIndex) > fitnesses.at(bestCandidateIndex))
                bestCandidateIndex = nextCandidateIndex;
        }

        // add the best candidate to the new population
        parents.push_back(population.at(bestCandidateIndex));
    }

    return parents;
}

std::vector<Schedule> PointCrossover(const std::vector<Schedule>& parents)
{
    std::vector<Schedule> newPopulation;

    for (int i = 0; i < parents.size(); ++i)
    {
        std::vector<Schedule> lovers;

        std::sample(
            parents.begin(),
            parents.end(),
            std::back_inserter(lovers),
            2,
            std::mt19937{std::random_device{}()}
        );

        const Schedule& lover1 = lovers.at(0);
        const Schedule& lover2 = lovers.at(1);

        Schedule child;

        int numEvents = lover1.events.size();

        int point = RandomIndex(numEvents);

        for (int j = 0; j < point; ++j)
        {
            child.events.push_back(Event());

            // crossover room
            child.events.back().RoomIndex = lover1.events.at(j).RoomIndex;

            // crossover facilitator
            child.events.back().FacilitatorIndex = lover1.events.at(j).FacilitatorIndex;

            // crossover time
            child.events.back().TimeIndex = lover1.events.at(j).TimeIndex;

        }

        for (int j = point; j < numEvents; ++j)
        {
            child.events.push_back(Event());

            // crossover room
            child.events.back().RoomIndex = lover2.events.at(j).RoomIndex;

            // crossover facilitator
            child.events.back().FacilitatorIndex = lover2.events.at(j).FacilitatorIndex;

            // crossover time
            child.events.back().TimeIndex = lover2.events.at(j).TimeIndex;

        }

        newPopulation.push_back(child);
    }

    return newPopulation;

}

std::vector<Schedule> Mutate(const std::vector<Schedule>& population, int numRooms, int numTimes, int numFacilitators, double mutationRate)
{
    std::vector<Schedule> newPopulation;

    for (Schedule newSchedule : population)
    {
        for (Event& event : newSchedule.events)
        {
            // mutate room
            if (CoinFlip(mutationRate))
                event.RoomIndex = RandomIndex(numRooms);
            
            // mutate time
            if (CoinFlip(mutationRate))
                event.TimeIndex = RandomIndex(numTimes);

            // mutate facilitator
            if (CoinFlip(mutationRate))
                event.FacilitatorIndex = RandomIndex(numFacilitators);
        }

        newPopulation.push_back(newSchedule);
    }

    return newPopulation;
}