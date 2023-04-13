
# Genetic Scheduling

### Summary

This program uses a genetic algorithm to generate a space utilization schedule for a client agency's activities. The schedule needs to determine the time slot, room, and facilitator for each activity. Each activity has a list of preferred and other facilitators, and the expected enrollment for each activity should be in a room big enough to hold it. The initial assignment is random, and the program will generate a population of random possible schedules and apply a genetic algorithm to improve it.

### Fitness Function
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

### Setup

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

### Example Program
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

### Average Fitness
![Average Fitness](docs/average_fitness.png)

### Mutation Rate
![Mutation Rate](docs/mutation_rate.png)


