#include "simlib.h"

/* Event type assignments. */

#define EVENT_ARRIVAL_PERSON_TERMINAL_1         	1	/* Event type for arrival of the bus to terminal 1. */
#define EVENT_ARRIVAL_PERSON_TERMINAL_2         	2	/* Event type for arrival of the bus to terminal 2. */
#define EVENT_ARRIVAL_PERSON_CAR_RENTAL         	3	/* Event type for arrival of the bus to car rental. */
#define EVENT_DEPARTURE       						4	/* Event type for departure of the bus from a particular location. */
#define EVENT_END_SIMULATION  						5	/* Event type for end of the simulation. */

/* Random-number stream assignments. */

#define STREAM_INTERARRIVAL_TERMINAL_1	1	/* Random-number stream for interarrival time at terminal 1. */
#define STREAM_INTERARRIVAL_TERMINAL_2	2	/* Random-number stream for interarrival time at terminal 2. */
#define STREAM_INTERARRIVAL_CAR_RENTAL	3	/* Random-number stream for interarrival time at car rental. */
#define STREAM_UNLOADING       			4	/* Random-number stream for unloading times. */
#define STREAM_LOADING					5	/* Random-number stream for loading times. */
#define STREAM_DESTINATION    			6	/* Random-number stream for determining destination of an arrival at the car rental. */

#define DESTINATION_TERMINAL_1 1
#define DESTINATION_TERMINAL_2 2
#define DESTINATION_CAR_RENTAL 3

#define LIST_TERMINAL_1 1
#define LIST_TERMINAL_2 2
#define LIST_CAR_RENTAL 3

/* Event function for arrival of the bus to terminal 1. */
void arrival_person_terminal_1 () {
	transfer[1] = sim_time;
	transfer[2] = DESTINATION_TERMINAL_2;
	list_file(LAST, LIST_TERMINAL_1);

	event_schedule(sim_time + expon(14, STREAM_INTERARRIVAL_TERMINAL_1), EVENT_ARRIVAL_PERSON_TERMINAL_1);
}

/* Event function for arrival of the bus to terminal 2. */
void arrival_person_terminal_2 () {
	transfer[1] = sim_time;
	transfer[2] = DESTINATION_CAR_RENTAL;
	list_file(LAST, LIST_TERMINAL_2);

	event_schedule(sim_time + expon(10, STREAM_INTERARRIVAL_TERMINAL_2), EVENT_ARRIVAL_PERSON_TERMINAL_2);
}

/* Event function for arrival of the bus to terminal 2. */
void arrival_person_car_rental () {
	transfer[1] = sim_time;
	transfer[2] = DESTINATION_TERMINAL_1;
	list_file(LAST, LIST_CAR_RENTAL);

	event_schedule(sim_time + expon(24, STREAM_INTERARRIVAL_CAR_RENTAL), EVENT_ARRIVAL_PERSON_CAR_RENTAL);
}

/* Event function for departure of the bus from a particular location. */
void depart (void) {
	
}

/* Function for generating statistics. */
void report (void) {
	
}

void init_model() {
	event_schedule(sim_time + expon(14, STREAM_INTERARRIVAL_TERMINAL_1), EVENT_ARRIVAL_PERSON_TERMINAL_1);
	event_schedule(sim_time + expon(10, STREAM_INTERARRIVAL_TERMINAL_2), EVENT_ARRIVAL_PERSON_TERMINAL_2);
	event_schedule(sim_time + expon(24, STREAM_INTERARRIVAL_CAR_RENTAL), EVENT_ARRIVAL_PERSON_CAR_RENTAL);
}

/* Main function. */
int main () {
	printf("start time: %d",sim_time);
	/* Initialize simlib. */
	init_simlib ();
	
	init_model();
	while (sim_time < 80 * 60 * 60) {
		timing();
		switch(next_event_type) {
			case EVENT_ARRIVAL_PERSON_TERMINAL_1:
				arrival_person_terminal_1();
				break;
			case EVENT_ARRIVAL_PERSON_TERMINAL_2:
				arrival_person_terminal_2();
				break;
			case EVENT_ARRIVAL_PERSON_CAR_RENTAL:
				arrival_person_car_rental();
				break;
		}
	}
	printf("Finish time: %d", sim_time);
	return 0;
}
