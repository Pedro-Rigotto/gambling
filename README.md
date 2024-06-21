This simulator runs a gambling system (https://i.imgur.com/UZLkq9o.png) a configurable amount of times. All the settings are in the #define section.

gambling.cpp is sequential code.

gambling.c has been parallelized using OpenMP.



To compile:

gcc -o gamblingcpp .\gambling.cpp

gcc .\gambling.c -o gambling -fopenmp



Timing results:

Parallel (C)         1.9171951 sec

Sequential (C++)    15.8637165 sec

Speedup                 8.2744   
