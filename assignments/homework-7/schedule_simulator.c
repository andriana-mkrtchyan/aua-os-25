#include <stdio.h>
#include <limits.h>

struct Process{
	int pid; //process id
	int arrival_time; //time when the process arrives in the system
	int burst_time; // CPU birst time required by the process
	int turnaround_time;//time taken from process arrival to its completion
	int waiting_time; //time a process spends waiting in the queue
	int response_time; // time from process arrival to the first execution
			   // (same as waiting time for non-preemptive algorithms)
};

int cmp_arrival_time(struct Process, struct Process);
int cmp_burst_time(struct Process, struct Process);
void insertion_sort(struct Process *processes, int nProc, int (*cmp)(struct Process, struct Process));
void print_info(struct Process *processes, int nProc, char *algo_name);
void fcfs(struct Process *processes, int nProc);
void sjf(struct Process *processes, int nProc);


int main(){

	int nProc; // number of simulated processes 
	
	printf("Enter the number of processes: ");
	scanf("%d", &nProc);
	if(nProc <= 0){
		printf("No process to simulate...");
		return -1;
	}

	struct Process processes[nProc]; // array to hold nProc processes


	// reading process arrival and burst times from the user
	for(int i = 0; i < nProc; i++){
		printf("Enter the arrival time and burst time for process %d: ", i+1);
		scanf("%d", &processes[i].arrival_time);
		scanf("%d", &processes[i].burst_time);
		processes[i].pid = i + 1;
	}
	
	// simulating fcfs
	fcfs(processes, nProc);

	// simulating sjf
	sjf(processes, nProc);

	return 0;
}


// A function that simulates how FCFS algorithm schedules CPU tasks
// *processes: 	array holding the processes to be scheduled
// nProc: 	number of processes in the array
void fcfs(struct Process *processes, int nProc){
	if(nProc <= 0){
		return;
	}
	else{
		insertion_sort(processes, nProc, cmp_arrival_time); // sort the processes 

		float avg_wt = 0; // accumulator for average waiting time
                float avg_tat = 0; // accumulator for average turnaround time
                float avg_rt = 0; // accumulator for average response time

		int current_time = 0;
		
		for(int i = 0; i < nProc; i++){
			if(current_time < processes[i].arrival_time){
				current_time = processes[i].arrival_time; // handling the cases where the CPU is idle
			}

			processes[i].waiting_time = current_time - processes[i].arrival_time;
							// as the array of processes is already sorted, current time signifies that 
							// we are currently starting the execution of i-th process
			
			processes[i].response_time = processes[i].waiting_time;
							// fcfs is non-preemptive, so response time is same as waiting time
							//
			processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;

		
			avg_wt += processes[i].waiting_time;
			avg_tat += processes[i].turnaround_time;
			avg_rt += processes[i].response_time;

			current_time += processes[i].burst_time; // burst_time time passed, so we update the current time
		}
	
		print_info(processes, nProc, "First Come First Served (FCFS)");
		printf("Average waiting time: %.2f\n", avg_wt/nProc);
		printf("Average turnaround time: %.2f\n", avg_tat/nProc);
		printf("Average response time: %.2f\n", avg_rt/nProc);
	
	}
	
}




// A function that simulates how SJF algorithm schedules CPU tasks
// *processes:  array holding the processes to be scheduled
// nProc:       number of processes in the array       
void sjf(struct Process *processes, int nProc){
	if(nProc <= 0){
		return;
	}
	else{
		// sort the processes based on their arrival time
		insertion_sort(processes, nProc, cmp_arrival_time);
		

                float avg_wt = 0; // accumulator for average waiting time
                float avg_tat = 0; // accumulator for average turnaround time
                float avg_rt = 0; // accumulator for average response time


		int current_time = 0;
		
		int nCompl = 0; // number of completed processes
		int completed[nProc]; // an array of flags to indicate whether a process is complete(1) or not(0)
		
		struct Process simulated[nProc]; // an array to store the references to processes as they are being processed
						 // kept in order not to change the real array 
		int j = 0; // operator to pass the simulated[] array

		// initialising the flag array
		for(int i = 0; i < nProc; i++){
			completed[i] = 0;
		}

		// while there is a process to be completed
		while(nCompl < nProc){

			int min_bt  = INT_MAX; // a var to keep the current minimum burt time of the processes in the queue
			int min_i = -1; // the index fo the process with min burst time
			int proc_found = 0; // flag to indicate whether there is a job to be processed at current time

			for(int i = 0; i < nProc; i++){
				if(completed[i]!= 1 && // if the process is not already completed
				   processes[i].arrival_time <= current_time && // and it has arrived in the queue by current_time
				   processes[i].burst_time < min_bt   // and it has the min burst_time among others in the queue
     			           )
				{
					min_bt = processes[i].burst_time; // it becomes the next process to be completed
					min_i = i;
					proc_found = 1;
				}
			}

			// if a job has been found to be processed at current time
			if(proc_found == 1){
				processes[min_i].waiting_time = current_time - processes[min_i].arrival_time;
				processes[min_i].response_time = processes[min_i].waiting_time;
				processes[min_i].turnaround_time = processes[min_i].waiting_time + processes[min_i].burst_time;
			
                        	avg_wt += processes[min_i].waiting_time;
                        	avg_tat += processes[min_i].turnaround_time;
                        	avg_rt += processes[min_i].response_time;

				completed[min_i] = 1; // mark the process as complete
                                current_time += processes[min_i].burst_time; // let burst_time time pass
                                nCompl++; // track the number of processes already completed
				
				simulated[j] = processes[min_i]; // add the recently processed job to simulation
				j++; // and wait for the next job
			}
			else{
				current_time++; // let time pass if no current processes were found in the queue
			}
		}

		// print the simulation results
		print_info(simulated, nProc, "Shortest Job First (SJF)");
		printf("Average waiting time: %.2f\n", avg_wt/nProc);
                printf("Average turnaround time: %.2f\n", avg_tat/nProc);
                printf("Average response time: %.2f\n", avg_rt/nProc);
		
	}
}

// simple insertion sort algorithm to provide stable sorting of the array
// *processes: 	array of processes to be sorted
// nProc: 	number of processes
// *cmp:	pointer to a comparator function taking two processes as argument
void insertion_sort(struct Process *processes, int nProc, int (*cmp)(struct Process, struct Process)){

	for(int i = 1; i < nProc; i++){
		struct Process temp = processes[i]; 
		int j = i - 1;

		while (j >= 0 && cmp(processes[j], temp) > 0){
			processes[j + 1] = processes[j];
			j--;
		}
		processes[j + 1] = temp;
	}

}


// function for printing the calculated result simulation
// *processes: 	array of processes 
// nProc: 	number of processes
// *algo_name:	name of the scheduling algorithm being simulated
void print_info(struct Process *processes, int nProc, char *algo_name){
	printf("\n=== %s ===\n", algo_name);
	
	printf("Gantt chart: |");
	// in the already sorted array of processes, I calculate the GANTT chart to demonstrate the process chunk in respect to its
	// burst time, i.e. the larger the burst time, the larger part of the chart the process takes
	
	int current_time = 0;
	 
	for(int i = 0; i < nProc; i++){
		
		 // If CPU is idle before this process
		if(processes[i].arrival_time > current_time){
            		int idle_time = processes[i].arrival_time - current_time;
	        	int padding = idle_time/2; // adjust scale if needed

            		printf("%*sIDLE%*s|", padding, "", padding, "");
            		current_time += idle_time;
       		}

	
		int padding = processes[i].burst_time/2;
		printf("%*sP%d%*s|",padding, "", processes[i].pid, padding, "");
		
		current_time += processes[i].burst_time;
	}

	printf("\n%-6s%-6s%-6s%-6s%-6s%-6s\n", "PID", "AT", "BT", "WT", "TAT", "RT");

	for(int i = 0; i < nProc; i++){
		printf("%-6d%-6d%-6d%-6d%-6d%-6d\n",
							processes[i].pid,
							processes[i].arrival_time,
							processes[i].burst_time,
							processes[i].waiting_time,
							processes[i].turnaround_time,
							processes[i].response_time);
	}
	printf("\n");
}

// a comparator function to serve as argument for sorting inside fcfs
// comparing two processes based on their arrival time
int cmp_arrival_time(struct Process a, struct Process b){
	return a.arrival_time - b.arrival_time;
}


// a comparator function to serve as helper inside sjf
// comparing two processes based on their burst time
int cmp_burst_time(struct Process a, struct Process b){
	return a.burst_time - b.burst_time;
}





