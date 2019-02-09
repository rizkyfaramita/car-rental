#include "simlib.h"

#define EVENT_ARRIVAL         	1	/* Event type for arrival of the bus to the rental. */
#define EVENT_DEPARTURE       	2	/* Event type for departure of the bus from a particular location. */
#define EVENT_END_SIMULATION  	3	/* Event type for end of the simulation. */

/* Random-number stream assignments. */

#define STREAM_INTERARRIVAL_1   1	/* Random-number stream for interarrival time at location 1. */
#define STREAM_INTERARRIVAL_2   2	/* Random-number stream for interarrival time at location 2. */
#define STREAM_INTERARRIVAL_3   3	/* Random-number stream for interarrival time at location 3. */
#define STREAM_UNLOADING       	4	/* Random-number stream for unloading times. */
#define STREAM_LOADING        	5	/* Random-number stream for loading times. */
#define STREAM_DESTINATION    	6	/* Random-number stream for determining destination of an arrival at the car rental. */

/* Event function for arrival of the bus to a particular location. */
void arrive (int new_job) {
	
}

/* Event function for departure of the bus from a particular location. */
void depart (void) {
	
}

/* Function for generating statistics. */
void report (void) {
	
}

/* Main function. */
int main () {
	/* Initialize simlib. */
	init_simlib ();
	
	/* Schedule the beginning of the simulation. */
	/* Schedule the end of the simulation. */
	/* Run simulation for 80 hours. */
	/* Generate report. */
	return 0;
}
