# readme

This file indicates how to run the file schedule_simulator.c

To run, first execute the file on console:
	
	gcc schedule_simulator.c -o <any_name_for_object_file>

	example command: 
		 gcc schedule_simulator.c -o csim

Then, call the executable:

	./<name_of_the_object_file>

	example command:
		./csim

Once executed, the program will ask for a number of processes to be simulated.
A positive integer needs to be passed as input.

Then, the program will ask for the arrival and burst times of each process, one by one.
Input those by putting a \space or \newline between arrival and burst times.

Finally, see the program simulate the schedulers.

* Note:	The program prints the GANTT chart of the schedulers based on the processing and burst times of the processes.
* 	e.g. if process sequence is P1, P2, P4, P3, the same sequence will be maintained in the chart, 
* 	and the length of the chunk illustration (|  P1  | or |P1| or |IDLE|) will be decided dynamically based 
*	on the burst time of each process. 
*
* 	If P1 ends at time=1 and P2 starts at time=2, the gap between the processes will be illustrated as |IDLE| 
*
* 	The program does not scale (reducing in size) paddings and chart size in case of very large burst times, e.g. 1000,
* 	so please do not test such for having consistent and beautiful output :)
*


