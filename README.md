
# Genetic Scheduling
- Jonathan Benson
- Intro to AI
- 4/15/2023
- https://github.com/jonathanbenson/genetic-scheduling

### Abstract

This program uses a genetic algorithm to generate a space utilization schedule for college activities (classes). The schedule needs to determine the time slot, room, and facilitator for each activity. Each activity has a list of preferred and other facilitators, and the expected enrollment for each activity should be in a room big enough to hold it. The initial assignment is random, and the program will generate a population of random possible schedules and apply a genetic algorithm to improve it.

## Setup

1. Clone the repository

To clone the repository and its submodules, open a terminal and run the following command:

`git clone --recurse-submodules https://github.com/jonathanbenson/genetic-scheduling`

2. Build the Project

To build the project, you need a C++17 compiler. Make sure that the compiler is installed on your system and available in your PATH.

Open a terminal and navigate to the root directory of the cloned repository. Then, run the following commands:

```
mkdir build
cd build
cmake ..
make
```

The above commands create a build directory, run CMake to generate the makefiles, and then run make to build the project.

3. Test the Project

To test the project, navigate to the build directory and run the executable:

```
cd build
./test
```

4. Run the Project

To run the project in the build directory, run the executable:

```
./main
```

## Implementation

#### Genome
The genome of the genetic algorithm is a schedule that consists of a set of activities whose mutable genes consist of...
1. Time
    - Multiple activities can take place at the same time in the schedule.
2. Facilitator
    - A facilitator is assigned to oversee each activity.
    - A facilitator can be assigned to multiple activities.
3. Room
    - Each activity is assigned a room.
    - Multiple activities can be assigned the same room and the same time, which may or may not hurt their fitness according to the fitness function.

#### Tournament Selection
A genetic algorithm is a type of optimization algorithm that uses a process inspired by natural selection to find optimal solutions to complex problems. In this specific implementation, the algorithm employs tournament selection as the selection method. This means that a subset of k individuals from the population is randomly selected to compete, and the fittest individual is chosen as the parent. The value of k determines the intensity of the selection pressure, with larger values increasing the pressure and favoring the fittest individuals.

Here is the function that implements tournament selection:

```c++
std::vector<Schedule> TournamentSelect(const std::vector<Schedule>& population, const std::vector<double>& fitnesses, int k)
{
    // get vector of population indices for later code
    std::vector<int> populationIndices;

    for (int i = 0; i < population.size(); ++i)
        populationIndices.push_back(i);


    std::vector<Schedule> parents;

    for (int i = 0; i < population.size(); ++i)
    {
        // sample k candidates
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
```


#### Uniform Crossover
The crossover method used in this algorithm is uniform, which means that each gene in the offspring is selected from one of the parents with equal probability. This allows for a diverse range of gene combinations to be produced and increases the chances of finding optimal solutions. The crossover rate can be adjusted to control the balance between exploration and exploitation.

Here is the function that implements uniform crossover:

```c++
std::vector<Schedule> UniformCrossover(const std::vector<Schedule>& parents)
{
    std::vector<Schedule> newPopulation;

    for (int i = 0; i < parents.size(); ++i)
    {
        // sample 2 parents for crossover
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

        // perform crossover
        Schedule child;

        for (int j = 0; j < lover1.events.size(); ++j)
        {
            child.events.push_back(Event());

            // activity remains the same regardless of the lover
            child.events.back().ActivityIndex = lover1.events.at(j).ActivityIndex;

            // crossover facilitator
            child.events.back().FacilitatorIndex = CoinFlip() ? lover1.events.at(j).FacilitatorIndex : lover2.events.at(j).FacilitatorIndex;

            // crossover room
            child.events.back().RoomIndex = CoinFlip() ? lover1.events.at(j).RoomIndex : lover2.events.at(j).RoomIndex;

            // crossover time
            child.events.back().TimeIndex = CoinFlip() ? lover1.events.at(j).TimeIndex : lover2.events.at(j).TimeIndex;

        }

        // add the new offspring to the new generation
        newPopulation.push_back(child);
    }

    return newPopulation;

}
```

#### Point Mutation
The mutation method employed in this genetic algorithm is point mutation. Point mutation randomly selects a gene from an individual and changes it to a new value. This introduces new genetic diversity into the population and allows the algorithm to explore the solution space more extensively. The mutation rate can also be adjusted to control the balance between exploration and exploitation. In this specific implementation, the mutation rate is halved over time if the average of the last n generational fitnesses is less than the fitness of the current generation. This adaptive mutation rate ensures that the algorithm does not get stuck in local optima and can continue to explore the solution space.

Here is the function that implements point mutation:

```c++
std::vector<Schedule> PointMutation(const std::vector<Schedule>& population, int numRooms, int numTimes, int numFacilitators, double mutationRate)
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
```

#### Fitness Function
- For each activity, fitness starts at 0.
- Activity is scheduled at the same time in the same room as another of the activities: -0.5
- Room size:
    - Activities is in a room too small for its expected enrollment: -0.5
    - Activities is in a room with capacity > 3 times expected enrollment: -0.2
    - Activities is in a room with capacity > 6 times expected enrollment: -0.4
    - Otherwise + 0.3
- Activities is overseen by a preferred facilitator: + 0.5
- Activities is overseen by another facilitator listed for that activity: +0.2
- Activities is overseen by some other facilitator: -0.1
- Facilitator load:
    - Activity facilitator is scheduled for only 1 activity in this time slot: + 0.2
    - Activity facilitator is scheduled for more than one activity at the same time: - 0.2
    - Facilitator is scheduled to oversee more than 4 activities total: -0.5
    - Facilitator is scheduled to oversee 1 or 2 activities*: -0.4
        - Exception: Dr. Tyler is committee chair and has other demands on his time. *No penalty if he’s only required to oversee < 2 activities.
    - If any facilitator scheduled for consecutive time slots: Same rules as for SLA 191 and SLA101 in consecutive time slots—see below.
- The 2 sections of SLA 101 are more than 4 hours apart: + 0.5
- Both sections of SLA 101 are in the same time slot: -0.5
- The 2 sections of SLA 191 are more than 4 hours apart: + 0.5
- Both sections of SLA 191 are in the same time slot: -0.5
- A section of SLA 191 and a section of SLA 101 are overseen in consecutive time slots (e.g., 10AM & 11 AM): +0.5
    - In this case only (consecutive time slots), one of the activities is in Roman or Beach,
and the other isn’t: -0.4
        - It’s fine if neither is in one of those buildings, of activity; we just want to avoid having
consecutive activities being widely separated.
- A section of SLA 191 and a section of SLA 101 are taught separated by 1 hour (e.g., 10
AM & 12:00 Noon): + 0.25
- A section of SLA 191 and a section of SLA 101 are taught in the same time slot: -0.25

Here is the function that implements the fitness function:

```c++
double FitnessFunction(const Schedule& s, const std::vector<Activity>& activities, const std::vector<Room>& rooms, const std::vector<double>& times, const std::vector<std::string>& facilitators)
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

                if (activities.at(e.ActivityIndex).Section != activities.at(f.ActivityIndex).Section)
                {
                    if (activities.at(e.ActivityIndex).Name == "SLA101" && activities.at(f.ActivityIndex).Name == "SLA101")
                    {
                        // The 2 sections of SLA 101 are more than 4 hours apart: + 0.5
                        if (std::abs(times.at(e.TimeIndex) - times.at(f.TimeIndex)) > 4.0)
                            fitness += .5;

                        // Both sections of SLA 101 are in the same time slot: -0.5
                        if (e.TimeIndex == f.TimeIndex)
                            fitness -= .5;
                    }

                    if (activities.at(e.ActivityIndex).Name == "SLA191" && activities.at(f.ActivityIndex).Name == "SLA191")
                    {
                        // The 2 sections of SLA 191 are more than 4 hours apart: + 0.5
                        if (std::abs(times.at(e.TimeIndex) - times.at(f.TimeIndex)) > 4.0)
                            fitness += .5;

                        // Both sections of SLA 191 are in the same time slot: -0.5
                        if (e.TimeIndex == f.TimeIndex)
                            fitness -= .5;
                    }
                }

                if (activities.at(e.ActivityIndex).Name == "SLA191" && activities.at(f.ActivityIndex).Name == "SLA101")
                {
                    // A section of SLA 191 and a section of SLA 101 are overseen in consecutive time slots (e.g., 10 AM & 11 AM): +0.5
                    if (abs(e.TimeIndex - f.TimeIndex) == 1)
                    {
                        // In this case only (consecutive time slots), one of the activities is in Roman or Beach, and the other isn’t: -0.4
                        if ((rooms.at(e.RoomIndex).Name == "Roman" || rooms.at(e.RoomIndex).Name == "Beach") && (rooms.at(f.RoomIndex).Name != "Roman" && rooms.at(f.RoomIndex).Name != "Beach"))
                            fitness -= .4;
                        else
                            fitness += .5;
                    }
                        
                    // A section of SLA 191 and a section of SLA 101 are taught separated by 1 hour (e.g., 10 AM & 12:00 Noon): + 0.25
                    else if (abs(e.TimeIndex - f.TimeIndex) == 2)
                        fitness += .25;

                    // A section of SLA 191 and a section of SLA 101 are taught in the same time slot: -0.25
                    else if (e.TimeIndex == f.TimeIndex)
                        fitness -= .25;
                }
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

            loadTotal += load;
        }

        if (facilitators.at(facilitatorIndex) == "Tyler")
        {
            // Facilitator is scheduled to oversee more than 4 activities total: -0.5
            if (loadTotal > 4)
                fitness -= .5;

            // Facilitator is scheduled to oversee 1 or 2 activities*: -0.4
            //     Exception: Dr. Tyler is committee chair and has other demands on his time. 
            //      *No penalty if he’s only required to oversee < 2 activities.
            else if (loadTotal > 1)
                fitness -= .4;
        }
        else
        {
            // Facilitator is scheduled to oversee more than 4 activities total: -0.5
            if (loadTotal > 4)
                fitness -= .5;

            // Facilitator is scheduled to oversee 1 or 2 activities*: -0.4
            else if (loadTotal < 3)
                fitness -= .4;
        }

        facilitatorIndex++;
    }

    return fitness;

}
```

#### Example Program
```
Genetic Scheduling Program

Population size: 500
# Generations: 50
Sample Size for Tournament Selection: 10
Initial Mutation Rate: 0.01
Mutation Rate Half-Life: 10

Evolving schedules...

Generation: 1, Avg. Fitness: 0.0008
Generation: 2, Avg. Fitness: 2.1587
Generation: 3, Avg. Fitness: 3.6788
Generation: 4, Avg. Fitness: 4.8948
Generation: 5, Avg. Fitness: 6.2999
Generation: 6, Avg. Fitness: 7.4313
Generation: 7, Avg. Fitness: 8.4918
Generation: 8, Avg. Fitness: 9.7767
Generation: 9, Avg. Fitness: 10.962
Generation: 10, Avg. Fitness: 12.0853
Generation: 11, Avg. Fitness: 12.5469
Generation: 12, Avg. Fitness: 13.3463
Generation: 13, Avg. Fitness: 13.9072
Generation: 14, Avg. Fitness: 14.7107
Generation: 15, Avg. Fitness: 15.532
Generation: 16, Avg. Fitness: 16.2827
Generation: 17, Avg. Fitness: 16.8521
Generation: 18, Avg. Fitness: 17.2298
Generation: 19, Avg. Fitness: 17.4365
Generation: 20, Avg. Fitness: 17.5817
Generation: 21, Avg. Fitness: 17.8959
Generation: 22, Avg. Fitness: 18.237
Generation: 23, Avg. Fitness: 18.4304
Generation: 24, Avg. Fitness: 18.452
Generation: 25, Avg. Fitness: 18.472
Generation: 26, Avg. Fitness: 18.4904
Generation: 27, Avg. Fitness: 18.5912
Generation: 28, Avg. Fitness: 18.5804
Generation: 29, Avg. Fitness: 18.5652
Generation: 30, Avg. Fitness: 18.646
Generation: 31, Avg. Fitness: 18.6708
Generation: 32, Avg. Fitness: 18.7184
Generation: 33, Avg. Fitness: 18.7484
Generation: 34, Avg. Fitness: 18.7204
Generation: 35, Avg. Fitness: 18.7276
Generation: 36, Avg. Fitness: 18.7664
Generation: 37, Avg. Fitness: 18.7584
Generation: 38, Avg. Fitness: 18.7804
Generation: 39, Avg. Fitness: 18.792
Generation: 40, Avg. Fitness: 18.7896
Generation: 41, Avg. Fitness: 18.7788
Generation: 42, Avg. Fitness: 18.7948
Generation: 43, Avg. Fitness: 18.79
Generation: 44, Avg. Fitness: 18.8
Generation: 45, Avg. Fitness: 18.78
Generation: 46, Avg. Fitness: 18.7848
Generation: 47, Avg. Fitness: 18.786
Generation: 48, Avg. Fitness: 18.794
Generation: 49, Avg. Fitness: 18.798
Generation: 50, Avg. Fitness: 18.794

Final schedule, Fitness: 18.8

10 SLA191A Roman201 Lock | SLA201B Beach301 Banks | SLA303B Frank119 Glen | SLA451B Loft310 Shaw
11 SLA101A Beach301 Lock | SLA201A Frank119 Banks | SLA304A Roman216 Glen | SLA451A Loft310 Singer
12 SLA291B Roman201 Zeldin | SLA303A Beach301 Banks | SLA449A Loft206 Shaw
13 SLA449B Loft206 Shaw
14 SLA101B Beach301 Lock | SLA291A Loft310 Zeldin | SLA394B Roman216 Singer
15 SLA191B Loft206 Zeldin | SLA304B Roman201 Glen | SLA394A Roman216 Singer
```

#### Average Fitness
![Average Fitness](https://github.com/jonathanbenson/genetic-scheduling/blob/main/docs/average_fitness.png?raw=true)

#### Mutation Rate
![Mutation Rate](https://github.com/jonathanbenson/genetic-scheduling/blob/main/docs/mutation_rate.png?raw=true)

## Reflection

#### What were the challenges in writing the program? Or did it seem to go smoothly from the beginning?

At first, I took an object oriented approach. I switched to a procedural approach early on the development process because most of the data of the program was centralized in the genome. This allowed me to stow away the data modeling the genome at the start of the program and only mutate indices corresponding to the genes in the genome. In this way, I was able to focus more on the algorithm and less on the implementation.

Another problem that I ran into was a bug in my crossover function. My first crossover function used the one-point crossover method, where a random index was chosen to split the genome of the child to include one parent’s genes on the left, and the other’s genes on the right. The mistake I made was corresponding the index of the crossover with the activities, instead of the genome. This mistake caused certain activities to be erased from the genome, and others duplicated. I fixed this bug by switching to a uniform crossover, where each gene in the child is randomly selected from either of the two parents.

#### What do you think of the schedule your program produced?

The schedule that my program produced is quite stellar:

```
10 SLA191A Roman201 Lock | SLA201B Beach301 Banks | SLA303B Frank119 Glen | SLA451B Loft310 Shaw
11 SLA101A Beach301 Lock | SLA201A Frank119 Banks | SLA304A Roman216 Glen | SLA451A Loft310 Singer
12 SLA291B Roman201 Zeldin | SLA303A Beach301 Banks | SLA449A Loft206 Shaw
13 SLA449B Loft206 Shaw
14 SLA101B Beach301 Lock | SLA291A Loft310 Zeldin | SLA394B Roman216 Singer
15 SLA191B Loft206 Zeldin | SLA304B Roman201 Glen | SLA394A Roman216 Singer
```

It has a fitness of approximately 18.8. The program outputs fitness in the
range 18-19.

Some aspects about it that stand out:
- Room size: All activities are assigned to rooms that are appropriate for
their expected enrollment.
- Scheduling conflicts: The schedule does not have any instances where
an activity is scheduled at the same time in the same room as another
activity.
- Facilitator load: No facilitator is scheduled to oversee more than 4
activities total, and Dr. Tyler is not assigned to any activities.
- Preferred facilitators: All activities are assigned acceptable facilitators
(preferred or other).

#### Does it have anything that still looks odd or out of place?

At time 1300, there is only one activity. It seems odd that there is only one activity scheduled for 1300 because it's a relatively large gap in the schedule, and it may not be the most efficient use of time and resources. The first two time slots have 3 activities scheduled, and it may be resourceful to allocate one of those activities to 1300.

#### How would you improve the program, or change the fitness function?

I think there are several ways to improve the program and fitness function. One approach is to incorporate additional constraints or preferences in the fitness function to better reflect the specific requirements of the problem. Another option is to adjust the weights of the fitness function components to reflect the relative importance of each factor. Additionally, different optimization algorithms could be experimented with, such as constraint programming or machine learning techniques, to potentially yield better results.

#### Anything else you feel like discussing, asking about, bragging about, etc.
In developing a scheduling program with a genetic algorithm, I've learned a lot about optimization algorithms and the importance of finetuning the fitness function to reflect the specific requirements of the scheduling problem. It's been a challenging but rewarding experience to experiment with different algorithms and parameters to see how they affect the quality of the generated schedule. I'm particularly proud of my ability to balance the different constraints and preferences while generating a feasible and optimized schedule. While there is always room for improvement, I'm confident that the skills and knowledge I've gained through this project will be valuable in my future endeavors.

