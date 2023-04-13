
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <matplot/matplot.h>
#include "Config.h"
#include "GA.h"
#include "defines.h"

int main()
{
    // seed the random number generator
    srand(time(0));

    // parse activities and facilitators
    std::pair<std::vector<Activity>, std::vector<std::string>> activitiesAndFacilitators
    = ParseActivitiesAndFacilitators(std::string(CONFIG_PATH) + "activities.json");

    std::vector<Activity> activities = activitiesAndFacilitators.first;
    std::vector<std::string> facilitators = activitiesAndFacilitators.second;

    // parse rooms
    std::vector<Room> rooms = ParseRooms(std::string(CONFIG_PATH) + "rooms.json");

    // parse times
    std::vector<double> times = ParseTimes(std::string(CONFIG_PATH) + "times.json");

    // init population
    std::vector<Schedule> generation = InitPopulation(activities.size(), rooms.size(), times.size(), facilitators.size(), POPULATION_SIZE);

    // for plotting
    std::vector<size_t> generations;
    std::vector<double> averageFitnesses;
    std::vector<double> mutationRates;

    double mutationFactor = 1.0;

    // run the GA
    for (int n = 1; n <= NUM_GENERATIONS; ++n)
    {

        // compute fitness of current generation
        std::vector<double> fitnesses = GetFitnesses(generation, activities, rooms, times, facilitators);

        // output current generation and average fitness
        double averageFitness = AverageFitness(fitnesses);

        // for plotting
        generations.push_back(n);
        averageFitnesses.push_back(averageFitness);
        mutationRates.push_back(INIT_MUTATION_RATE * mutationFactor);
        
        // output the current generation and its average fitness
        std::cout << "Generation: " << n << ", Avg. Fitness: " << averageFitness << std::endl;

        // select best candidates for crossover
        std::vector<Schedule> bestCandidates = TournamentSelect(generation, fitnesses, TOURNAMENT_SELECTION_SAMPLE_SIZE);

        // crossover new generation
        generation = PointCrossover(bestCandidates);

        // mutate new generation
        generation = Mutate(generation, rooms.size(), times.size(), facilitators.size(), INIT_MUTATION_RATE * mutationFactor);

        // halve the mutation if the current average fitness is greater than the average of the last n average fitnesses
        if (averageFitnesses.size() >= MUTATION_HALF_LIFE && averageFitness > AverageOfLastNValues(averageFitnesses, MUTATION_HALF_LIFE))
                mutationFactor /= 2;

    }

    matplot::plot(generations, averageFitnesses, "-o")->marker_indices(generations);
    matplot::title("Average Fitness");
    matplot::xlabel("Generation");
    matplot::ylabel("Average Fitness");

    matplot::show();

    matplot::plot(generations, mutationRates, "-o")->marker_indices(generations);
    matplot::title("Mutation Rate");
    matplot::xlabel("Generation");
    matplot::ylabel("Mutation Rate");

    matplot::show();

    return 0;
}