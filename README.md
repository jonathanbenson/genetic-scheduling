
# Genetic Scheduling

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
Mutation Rate Half-Life: 5

Evolving schedules...

Generation: 1, Avg. Fitness: 2.9038
Generation: 2, Avg. Fitness: 5.2128
Generation: 3, Avg. Fitness: 7.1234
Generation: 4, Avg. Fitness: 8.5704
Generation: 5, Avg. Fitness: 9.6628
Generation: 6, Avg. Fitness: 10.7124
Generation: 7, Avg. Fitness: 11.7128
Generation: 8, Avg. Fitness: 12.8638
Generation: 9, Avg. Fitness: 13.894
Generation: 10, Avg. Fitness: 15.0376
Generation: 11, Avg. Fitness: 15.7056
Generation: 12, Avg. Fitness: 16.283
Generation: 13, Avg. Fitness: 16.8144
Generation: 14, Avg. Fitness: 17.4146
Generation: 15, Avg. Fitness: 17.9742
Generation: 16, Avg. Fitness: 18.2578
Generation: 17, Avg. Fitness: 18.4286
Generation: 18, Avg. Fitness: 18.5452
Generation: 19, Avg. Fitness: 18.6056
Generation: 20, Avg. Fitness: 18.6888
Generation: 21, Avg. Fitness: 18.7556
Generation: 22, Avg. Fitness: 18.8196
Generation: 23, Avg. Fitness: 18.89
Generation: 24, Avg. Fitness: 18.92
Generation: 25, Avg. Fitness: 18.9188
Generation: 26, Avg. Fitness: 18.9356
Generation: 27, Avg. Fitness: 18.9476
Generation: 28, Avg. Fitness: 18.942
Generation: 29, Avg. Fitness: 18.9636
Generation: 30, Avg. Fitness: 18.958
Generation: 31, Avg. Fitness: 18.9712
Generation: 32, Avg. Fitness: 18.9792
Generation: 33, Avg. Fitness: 18.974
Generation: 34, Avg. Fitness: 18.9848
Generation: 35, Avg. Fitness: 18.9936
Generation: 36, Avg. Fitness: 18.9948
Generation: 37, Avg. Fitness: 18.9956
Generation: 38, Avg. Fitness: 18.9912
Generation: 39, Avg. Fitness: 18.9988
Generation: 40, Avg. Fitness: 18.9916
Generation: 41, Avg. Fitness: 18.9888
Generation: 42, Avg. Fitness: 18.9848
Generation: 43, Avg. Fitness: 18.9784
Generation: 44, Avg. Fitness: 18.9748
Generation: 45, Avg. Fitness: 18.9892
Generation: 46, Avg. Fitness: 18.9856
Generation: 47, Avg. Fitness: 18.994
Generation: 48, Avg. Fitness: 18.9892
Generation: 49, Avg. Fitness: 18.9928
Generation: 50, Avg. Fitness: 18.9928

Final schedule, Fitness: 18.9988

10 SLA191A Beach201 Banks | SLA449B Loft206 Tyler | SLA451A Loft310 Shaw 
11 SLA201B Beach201 Glen | SLA394B Slater3 Singer | SLA449A Loft206 Shaw 
12 SLA201A Roman201 Zeldin | SLA304B Beach201 Tyler 
13 SLA303A Frank119 Glen | SLA304A Roman201 Tyler | SLA451B Loft310 Singer 
14 SLA100A Roman201 Glen | SLA291A Loft310 Singer | SLA291B Frank119 Zeldin | SLA303B Beach201 Banks 
15 SLA100B Loft310 Lock | SLA191B Beach301 Banks | SLA394A Roman216 Singer
```

### Average Fitness
![Average Fitness](docs/average_fitness.png)

### Mutation Rate
![Mutation Rate](docs/mutation_rate.png)


