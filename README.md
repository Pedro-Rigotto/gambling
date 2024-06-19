gambling.cpp is sequential code.
gambling.c has been parallelized using OpenMP.

PS C:\Users\Pedro\Downloads\gambling> gcc -o gamblingcpp .\gambling.cpp    
PS C:\Users\Pedro\Downloads\gambling> gcc .\gambling.c -o gambling -fopenmp
PS C:\Users\Pedro\Downloads\gambling> Measure-Command { .\gambling.exe }     


Days              : 0
Hours             : 0
Minutes           : 0
Seconds           : 1
Milliseconds      : 917
Ticks             : 19171951
TotalDays         : 2,21897581018519E-05
TotalHours        : 0,000532554194444444
TotalMinutes      : 0,0319532516666667
TotalSeconds      : 1,9171951
TotalMilliseconds : 1917,1951



PS C:\Users\Pedro\Downloads\gambling> Measure-Command { .\gamblingcpp.exe }


Days              : 0
Hours             : 0
Minutes           : 0
Seconds           : 15
Milliseconds      : 863
Ticks             : 158637165
TotalDays         : 0,000183607829861111
TotalHours        : 0,00440658791666667
TotalMinutes      : 0,264395275
TotalSeconds      : 15,8637165
TotalMilliseconds : 15863,7165


