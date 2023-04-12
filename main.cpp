
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "Config.h"
#include "GA.h"

#define POPULATION_SIZE 100
#define NUM_GENERATIONS 100
#define TOURNAMENT_SELECTION_SAMPLE_SIZE 5
#define MUTATION_RATE .01

int main()
{
    // seed the random number generator
    srand(time(0));

    // parse activities and facilitators
    std::pair<std::vector<Activity>, std::vector<std::string>> activitiesAndFacilitators
    = ParseActivitiesAndFacilitators("./config/activities.json");

    std::vector<Activity> activities = activitiesAndFacilitators.first;
    std::vector<std::string> facilitators = activitiesAndFacilitators.second;

    // parse rooms
    std::vector<Room> rooms = ParseRooms("./config/rooms.json");

    // parse times
    std::vector<double> times = ParseTimes("./config/times.json");

    // init population
    std::vector<Schedule> generation = InitPopulation(activities.size(), rooms.size(), times.size(), facilitators.size(), POPULATION_SIZE);

    // run the GA
    for (int n = 0; n < NUM_GENERATIONS; ++n)
    {

        // compute fitness of current generation
        std::vector<double> fitnesses = GetFitnesses(generation, activities, rooms, times, facilitators);

        // output current generation and average fitness
        double averageFitness = AverageFitness(fitnesses);

        std::cout << "Generation: " << n + 1 << ", Avg. Fitness: " << averageFitness << std::endl;

        // select best candidates for crossover
        std::vector<Schedule> bestCandidates = TournamentSelect(generation, fitnesses, TOURNAMENT_SELECTION_SAMPLE_SIZE);

        // crossover new generation
        generation = UniformCrossover(bestCandidates);

        // mutate new generation
        generation = Mutate(generation, rooms.size(), times.size(), facilitators.size(), MUTATION_RATE);

    }


    return 0;
}