# Bus_System_Management
A basic system used to manage a bus system in city.
# 1. Introduction
In big cities, public transport is an important object of the city's overall infrastructure. Public transport is one of the methods of transportation for modern people in big cities, especially buses.

The bus transport system has many routes. Each route will be assigned with a fixed code, originating stop (first stop), terminus (last stop) and travel time to travel across the route. Everyday, each route will have many buses going from the first to the last stop. To differentiate between buses on the same route, people use license plate of vehicles and departure time.
# 2. Instruction 
Each data-processing command is a sequence of characters. Each command begins with a keyword (the bold word in the below-description) and is followed by parameters (the word in "<" and ">" in the below-description). There is exactly a space between the command and the parameters. There should be no spaces before the command keyword and no spaces after the last parameter. Some last parameters can be optional (with or without the command), these parameters will be placed in "[" and "]" in the below-description. When a command does not provide the correct number of parameters or does not have the correct type of the parameter as described or has spaces that are not as described, the command will not be executed and return "-1".
- CODE : a sequence of characters representing the route code.
- LP : stand for "License Plate", a sequence of characters that stores the value of the license plate of the bus.
- CASE : a binary value, if true, the bus goes from the start to the end (outward); otherwise, the bus goes in the opposite direction (return).
- TIME : an integer (representing time according to ISO standard) representing time.
- N : maximum number of trips for all routes. 
# 3. Installation
- Download the "main.cpp" file 
- Run the following commands

```sh
$ g++ main.cpp -c
$ g++ main.cpp
$ .\a.exe
```

# 4. Command List
```sh
$ SQ <N>
```
Set the maximum number of trips for all routes. This command is executed only one time in the program and before all other commands. 
```sh
$ INS <CODE> <LP> [<CASE>] <TIME_A> <TIME_B>
```
Insert a bus trip with license plate "LP" of the route with code "CODE" with departure time "TIME_A", arrive at the last stop at "TIME_B".
The command is executed successfully when there is no bus trip on the same route with the same departure time. In case the license plate has existed, the departure time "TIME_A" has to be later than the previous arrival time. When the command is executed successfully, return the number of saved license plates of the route, otherwise return -1. (Assume that a license plate can only make trips on a fixed route).
```sh
$ DEL <CODE> [>TIME_A>] [<TIME_B>]
```
Delete the saved trips of the route "CODE" which have the departure time between "TIME_A" and "TIME_B". The command returns the number of trips delete from the data set.
```sh
$ CS <CODE> <TIME> [<CASE>]
```
Return the number of trips that have started but have not yet arrived at the bus stop of the route with code "CODE" at the considered time "TIME". When it has the value "CASE", it will return the correct number of trips corresponding to outward trips or return trips, otherwise it will return all the trips which are satisfied in both directions.
```sh
$ CE <CODE> <TIME> [<CASE>]
```
Return the number of trips that have ended of the route with code "CODE" at the considered time "TIME". When we have value "CASE", it will return the correct number of trips corresponding to outward trips or return trips, otherwise it will return all the trips which are satisfied in both directions
```sh
$ GS <CODE> <TIME> [<CASE>]
```
Return the license plate of the bus trip of the route with code "CODE" which has started at the time closest to the considered time "TIME". When we have value "CASE", it need to return the correct trip corresponding to outward trips or return trips, otherwise, it will consider both directions. In case there is no trip that is satisfied, return -1. In case considering both directions, if there are 2 satisfied trips, return the outward trip.
```sh
$ GE <CODE> <TIME> [<CASE>]
```
Return the license plate of the bus trip of the route with code "CODE" which has ended at the time closest to the considered time "TIME". When we have value "CASE", it need to return the correct trip corresponding to outward trips or return trips, otherwise, we will consider both directions. In case there is no trip that is satisfied, return -1. In case considering both directions, if there are 2 satisfied trips, return the outward trip.
# 5. Mode
In mode in which users directly provide the command to manipulate the System, Just type the command satisfied the above-description. Besides, there are a command that print the current system, you will be noticed when run the program.

Or in mode in which users can change the source code in order to manipulate the inside code. You need to create an object like the following:
```sh
$ BusSystem *bs = new BusSystem;
```
After that, you can type your command by using the "query" method of the BusSystem class.
```sh
$ bs->query("SQ 10");
$ bs->query("INS A12B 5D-23342 1235 5678");
$ bs->query("INS B23A 31RE-555 0 1235 9121");
```
# 6. Conclusion
Feel free with the software
