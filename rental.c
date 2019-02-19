#include "simlib.h"

#define EVENT_ARRIVAL_PERSON_TERMINAL_1   1
#define EVENT_ARRIVAL_PERSON_TERMINAL_2   2
#define EVENT_ARRIVAL_PERSON_CAR_RENTAL   3
#define EVENT_ARRIVAL_BUS_TERMINAL_1      4
#define EVENT_ARRIVAL_BUS_TERMINAL_2      5
#define EVENT_ARRIVAL_BUS_CAR_RENTAL      6
#define EVENT_DEPARTURE_BUS_TERMINAL_1    7
#define EVENT_DEPARTURE_BUS_TERMINAL_2    8
#define EVENT_DEPARTURE_BUS_CAR_RENTAL    9
#define EVENT_UNLOAD_PERSON_TERMINAL_1    10
#define EVENT_UNLOAD_PERSON_TERMINAL_2    11
#define EVENT_UNLOAD_PERSON_CAR_RENTAL    12
#define EVENT_LOAD_PERSON_TERMINAL_1      13
#define EVENT_LOAD_PERSON_TERMINAL_2      14
#define EVENT_LOAD_PERSON_CAR_RENTAL      15
#define EVENT_END_SIMULATION              16

#define STREAM_INTERARRIVAL_TERMINAL_1  1
#define STREAM_INTERARRIVAL_TERMINAL_2  2
#define STREAM_INTERARRIVAL_CAR_RENTAL  3
#define STREAM_UNLOADING                4
#define STREAM_LOADING                  5
#define STREAM_DESTINATION              6

#define DESTINATION_TERMINAL_1 1
#define DESTINATION_TERMINAL_2 2
#define DESTINATION_CAR_RENTAL 3

#define LIST_TERMINAL_1 1
#define LIST_TERMINAL_2 2
#define LIST_CAR_RENTAL 3
#define LIST_BUS_TO_TERMINAL_1  4
#define LIST_BUS_TO_TERMINAL_2  5
#define LIST_BUS_TO_CAR_RENTAL  6

#define DATA_ARRIVAL_TIME 1
#define DATA_DESTINATION  2

#define VARIABLE_NQ_TERMINAL_1 1
#define VARIABLE_NQ_TERMINAL_2 2
#define VARIABLE_NQ_CAR_RENTAL 3
#define VARIABLE_DELAY_TERMINAL_1 4
#define VARIABLE_DELAY_TERMINAL_2 5
#define VARIABLE_DELAY_CAR_RENTAL 6
#define VARIABLE_NQ_BUS 7
#define VARIABLE_BUS_STOP_TERMINAL_1 8
#define VARIABLE_BUS_STOP_TERMINAL_2 9
#define VARIABLE_BUS_STOP_CAR_RENTAL 10
#define VARIABLE_BUS_LOOP 11
#define VARIABLE_PERSON_SYSTEM 12

#define MAX_BUS_SIZE 20

double bus_last_arrival = 0.0;

int list_bus_size() {return list_size[LIST_BUS_TO_TERMINAL_1] + list_size[LIST_BUS_TO_TERMINAL_2] + list_size[LIST_BUS_TO_CAR_RENTAL]; }

double max(double a, double b) { return a > b ? a : b; }

void arrival_person_terminal_1 () {
	transfer[DATA_ARRIVAL_TIME] = sim_time;
	transfer[DATA_DESTINATION] = DESTINATION_CAR_RENTAL;
	list_file(LAST, LIST_TERMINAL_1);

  timest(list_size[LIST_TERMINAL_1], VARIABLE_NQ_TERMINAL_1);

	event_schedule(sim_time + expon(60.0 * 60.0 / 14.0, STREAM_INTERARRIVAL_TERMINAL_1), EVENT_ARRIVAL_PERSON_TERMINAL_1);
}

void arrival_bus_terminal_1() {
  bus_last_arrival = sim_time;
  if (list_size[LIST_BUS_TO_TERMINAL_1] > 0) {
    event_schedule(sim_time + uniform(16, 24, STREAM_UNLOADING), EVENT_UNLOAD_PERSON_TERMINAL_1);
  }else if (list_size[LIST_TERMINAL_1] > 0 && list_bus_size() < MAX_BUS_SIZE) {
    event_schedule(sim_time + uniform(15, 25, STREAM_LOADING), EVENT_LOAD_PERSON_TERMINAL_1);
  }else {
    event_schedule(sim_time + 5.0 * 60.0, EVENT_DEPARTURE_BUS_TERMINAL_1);
  }
}

void departure_bus_terminal_1() {
  if ((sim_time - bus_last_arrival) < (5.0 * 60.0)){
    event_schedule(bus_last_arrival + 5.0 * 60.0, EVENT_DEPARTURE_BUS_TERMINAL_1);
  }else {
    event_schedule(sim_time + 1.0 / 30.0 * 60.0 * 60.0, EVENT_ARRIVAL_BUS_TERMINAL_2);
  }
}

void unload_person_terminal_1() {
  
  list_remove(FIRST, LIST_BUS_TO_TERMINAL_1);

  if (list_size[LIST_BUS_TO_TERMINAL_1] > 0) {
    event_schedule(sim_time + uniform(16, 24, STREAM_UNLOADING), EVENT_UNLOAD_PERSON_TERMINAL_1);
  }else if (list_size[LIST_TERMINAL_1] > 0 && list_bus_size() < MAX_BUS_SIZE) {
    event_schedule(sim_time + uniform(15, 25, STREAM_LOADING ), EVENT_LOAD_PERSON_TERMINAL_1);
  }else {
    event_schedule(sim_time, EVENT_DEPARTURE_BUS_TERMINAL_1);
  }
}

void load_person_terminal_1() {
  list_remove(FIRST, LIST_TERMINAL_1);
  timest(list_size[LIST_TERMINAL_1], VARIABLE_NQ_TERMINAL_1);
  list_file(LAST, LIST_BUS_TO_CAR_RENTAL);
  if (list_size[LIST_TERMINAL_1] > 0 && list_bus_size() < MAX_BUS_SIZE) {
    event_schedule(sim_time + uniform(15, 25, STREAM_LOADING), EVENT_LOAD_PERSON_TERMINAL_1);
  }else {
    event_schedule(sim_time, EVENT_DEPARTURE_BUS_TERMINAL_1);
  }
}

void arrival_person_terminal_2 () {
	transfer[DATA_ARRIVAL_TIME] = sim_time;
	transfer[DATA_DESTINATION] = DESTINATION_CAR_RENTAL;
	list_file(LAST, LIST_TERMINAL_2);

	event_schedule(sim_time + expon(60.0 * 60.0 / 10.0, STREAM_INTERARRIVAL_TERMINAL_2), EVENT_ARRIVAL_PERSON_TERMINAL_2);
}

void arrival_bus_terminal_2() {
  bus_last_arrival = sim_time;
  if (list_size[LIST_BUS_TO_TERMINAL_2] > 0) {
    event_schedule(sim_time + uniform(16, 24, STREAM_UNLOADING), EVENT_UNLOAD_PERSON_TERMINAL_2);
  }else if (list_size[LIST_TERMINAL_2] > 0 && list_bus_size() < MAX_BUS_SIZE) {
    event_schedule(sim_time + uniform(15, 25, STREAM_LOADING), EVENT_LOAD_PERSON_TERMINAL_2);
  }else {
    event_schedule(sim_time + 5.0 * 60.0, EVENT_DEPARTURE_BUS_TERMINAL_2);
  }
}

void departure_bus_terminal_2() {
  if ((sim_time - bus_last_arrival) < (5.0 * 60.0)){
    event_schedule(bus_last_arrival + 5.0 * 60.0, EVENT_DEPARTURE_BUS_TERMINAL_2);
  }else {
    event_schedule(sim_time + 4.5 / 30.0 * 60.0 * 60.0, EVENT_ARRIVAL_BUS_CAR_RENTAL);
  }
}

void unload_person_terminal_2() {
  
  list_remove(FIRST, LIST_BUS_TO_TERMINAL_2);

  if (list_size[LIST_BUS_TO_TERMINAL_2] > 0) {
    event_schedule(sim_time + uniform(16, 24, STREAM_UNLOADING), EVENT_UNLOAD_PERSON_TERMINAL_2);
  }else if (list_size[LIST_TERMINAL_2] > 0 && list_bus_size() < MAX_BUS_SIZE) {
    event_schedule(sim_time + uniform(15, 25, STREAM_LOADING ), EVENT_LOAD_PERSON_TERMINAL_2);
  }else {
    event_schedule(sim_time, EVENT_DEPARTURE_BUS_TERMINAL_2);
  }
}

void load_person_terminal_2() {
  list_remove(FIRST, LIST_TERMINAL_2);
  list_file(LAST, LIST_BUS_TO_CAR_RENTAL);
  if (list_size[LIST_TERMINAL_2] > 0 && list_bus_size() < MAX_BUS_SIZE) {
    event_schedule(sim_time + uniform(15, 25, STREAM_LOADING), EVENT_LOAD_PERSON_TERMINAL_2);
  }else {
    event_schedule(sim_time, EVENT_DEPARTURE_BUS_TERMINAL_2);
  }
}

void arrival_person_car_rental () {
	transfer[DATA_ARRIVAL_TIME] = sim_time;

  double prob_distrib[3] = {0, 0.583, 1};
  if (random_integer(prob_distrib, STREAM_DESTINATION) == 1)
	  transfer[DATA_DESTINATION] = DESTINATION_TERMINAL_1;
  else
    transfer[DATA_DESTINATION] = DESTINATION_TERMINAL_2;

	list_file(LAST, LIST_CAR_RENTAL);

	event_schedule(sim_time + expon(60.0 * 60.0 / 24.0, STREAM_INTERARRIVAL_CAR_RENTAL), EVENT_ARRIVAL_PERSON_CAR_RENTAL);
}

void arrival_bus_car_rental() {
  bus_last_arrival = sim_time;
  if (list_size[LIST_BUS_TO_CAR_RENTAL] > 0) {
    event_schedule(sim_time + uniform(16, 24, STREAM_UNLOADING), EVENT_UNLOAD_PERSON_CAR_RENTAL);
  }else if (list_size[LIST_CAR_RENTAL] > 0 && list_bus_size() < MAX_BUS_SIZE) {
    event_schedule(sim_time + uniform(15, 25, STREAM_LOADING), EVENT_LOAD_PERSON_CAR_RENTAL);
  }else {
    event_schedule(sim_time + 5.0 * 60.0, EVENT_DEPARTURE_BUS_CAR_RENTAL);
  }
}

void departure_bus_car_rental() {
  if ((sim_time - bus_last_arrival) < (5.0 * 60.0)){
    event_schedule(bus_last_arrival + 5.0 * 60.0, EVENT_DEPARTURE_BUS_CAR_RENTAL);
  }else {
    event_schedule(sim_time + 4.5 / 30.0 * 60.0 * 60.0, EVENT_ARRIVAL_BUS_TERMINAL_1);
  }
}

void unload_person_car_rental() {
  
  list_remove(FIRST, LIST_BUS_TO_CAR_RENTAL);

  if (list_size[LIST_BUS_TO_CAR_RENTAL] > 0) {
    event_schedule(sim_time + uniform(16, 24, STREAM_UNLOADING), EVENT_UNLOAD_PERSON_CAR_RENTAL);
  }else if (list_size[LIST_CAR_RENTAL] > 0 && list_bus_size() < MAX_BUS_SIZE) {
    event_schedule(sim_time + uniform(15, 25, STREAM_LOADING ), EVENT_LOAD_PERSON_CAR_RENTAL);
  }else {
    event_schedule(sim_time, EVENT_DEPARTURE_BUS_CAR_RENTAL);
  }
}

void load_person_car_rental() {
  list_remove(FIRST, LIST_CAR_RENTAL);
  list_file(LAST, LIST_BUS_TO_CAR_RENTAL);
  if (list_size[LIST_CAR_RENTAL] > 0 && list_bus_size() < MAX_BUS_SIZE) {
    event_schedule(sim_time + uniform(15, 25, STREAM_LOADING), EVENT_LOAD_PERSON_CAR_RENTAL);
  }else {
    event_schedule(sim_time, EVENT_DEPARTURE_BUS_CAR_RENTAL);
  }
}

void init_model() {
	event_schedule(sim_time + expon(60.0 * 60.0 / 14.0, STREAM_INTERARRIVAL_TERMINAL_1), EVENT_ARRIVAL_PERSON_TERMINAL_1);
	event_schedule(sim_time + expon(60.0 * 60.0 / 10.0, STREAM_INTERARRIVAL_TERMINAL_2), EVENT_ARRIVAL_PERSON_TERMINAL_2);
	event_schedule(sim_time + expon(60.0 * 60.0 / 24.0, STREAM_INTERARRIVAL_CAR_RENTAL), EVENT_ARRIVAL_PERSON_CAR_RENTAL);
  event_schedule(sim_time + 4.5 / 30.0 * 60.0 * 60.0, EVENT_ARRIVAL_BUS_TERMINAL_1); 
  event_schedule(sim_time + 80.0 * 60.0 * 60.0, EVENT_END_SIMULATION);

  sampst(0, VARIABLE_NQ_TERMINAL_1);
  sampst(0, VARIABLE_NQ_TERMINAL_2);
  sampst(0, VARIABLE_NQ_CAR_RENTAL);
  sampst(0, VARIABLE_DELAY_TERMINAL_1);
  sampst(0, VARIABLE_DELAY_TERMINAL_2);
  sampst(0, VARIABLE_DELAY_CAR_RENTAL);
  sampst(0, VARIABLE_NQ_BUS);
  sampst(0, VARIABLE_BUS_STOP_TERMINAL_1);
  sampst(0, VARIABLE_BUS_STOP_TERMINAL_2);
  sampst(0, VARIABLE_BUS_STOP_CAR_RENTAL);
  sampst(0, VARIABLE_BUS_LOOP);
  sampst(0, VARIABLE_PERSON_SYSTEM);
}

void log_event() {
  switch(next_event_type) {
    case EVENT_ARRIVAL_PERSON_TERMINAL_1:
      printf("[ %.2lf ] EVENT_ARRIVAL_PERSON_TERMINAL_1\n", sim_time);      
      break;
    case EVENT_ARRIVAL_PERSON_TERMINAL_2:
      printf("[ %.2lf ] EVENT_ARRIVAL_PERSON_TERMINAL_2\n", sim_time);      
      break;
    case EVENT_ARRIVAL_PERSON_CAR_RENTAL:
      printf("[ %.2lf ] EVENT_ARRIVAL_PERSON_CAR_RENTAL\n", sim_time);      
      break;
    case EVENT_ARRIVAL_BUS_TERMINAL_1:
        printf("[ %.2lf ] EVENT_ARRIVAL_BUS_TERMINAL_1\n", sim_time);     
        break;
    case EVENT_ARRIVAL_BUS_TERMINAL_2:
      printf("[ %.2lf ] EVENT_ARRIVAL_BUS_TERMINAL_2\n", sim_time);     
      break;
    case EVENT_ARRIVAL_BUS_CAR_RENTAL:
      printf("[ %.2lf ] EVENT_ARRIVAL_BUS_CAR_RENTAL\n", sim_time);     
      break;
    case EVENT_DEPARTURE_BUS_TERMINAL_1:
      printf("[ %.2lf ] EVENT_DEPARTURE_BUS_TERMINAL_1\n", sim_time);     
      break;
    case EVENT_DEPARTURE_BUS_TERMINAL_2:
      printf("[ %.2lf ] EVENT_DEPARTURE_BUS_TERMINAL_2\n", sim_time);     
      break;
    case EVENT_DEPARTURE_BUS_CAR_RENTAL:
      printf("[ %.2lf ] EVENT_DEPARTURE_BUS_CAR_RENTAL\n", sim_time);     
      break;
    case EVENT_UNLOAD_PERSON_TERMINAL_1:
      printf("[ %.2lf ] EVENT_UNLOAD_PERSON_TERMINAL_1\n", sim_time);     
      break;
    case EVENT_UNLOAD_PERSON_TERMINAL_2:
      printf("[ %.2lf ] EVENT_UNLOAD_PERSON_TERMINAL_2\n", sim_time);     
      break;
    case EVENT_UNLOAD_PERSON_CAR_RENTAL:
      printf("[ %.2lf ] EVENT_UNLOAD_PERSON_CAR_RENTAL\n", sim_time);     
      break;
    case EVENT_LOAD_PERSON_TERMINAL_1:
        printf("[ %.2lf ] EVENT_LOAD_PERSON_TERMINAL_1\n", sim_time);     
        break;
    case EVENT_LOAD_PERSON_TERMINAL_2:
      printf("[ %.2lf ] EVENT_LOAD_PERSON_TERMINAL_2\n", sim_time);     
      break;
    case EVENT_LOAD_PERSON_CAR_RENTAL:
      printf("[ %.2lf ] EVENT_LOAD_PERSON_CAR_RENTAL\n", sim_time);     
      break;
  }
}

int main () {
	printf("start time: %.5f",sim_time);
	init_simlib ();
	init_model();
	while (next_event_type != EVENT_END_SIMULATION) {
		timing();
    log_event();
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
      case EVENT_ARRIVAL_BUS_TERMINAL_1:
        arrival_bus_terminal_1();
        break;
      case EVENT_ARRIVAL_BUS_TERMINAL_2:
        arrival_bus_terminal_2();
        break;
      case EVENT_ARRIVAL_BUS_CAR_RENTAL:
        arrival_bus_car_rental();
        break;
      case EVENT_DEPARTURE_BUS_TERMINAL_1:
        departure_bus_terminal_1();
        break;
      case EVENT_DEPARTURE_BUS_TERMINAL_2:
        departure_bus_terminal_2();
        break;
      case EVENT_DEPARTURE_BUS_CAR_RENTAL:
        departure_bus_car_rental();
        break;
      case EVENT_UNLOAD_PERSON_TERMINAL_1:
        unload_person_terminal_1();
        break;
      case EVENT_UNLOAD_PERSON_TERMINAL_2:
        unload_person_terminal_2();
        break;
      case EVENT_UNLOAD_PERSON_CAR_RENTAL:
        unload_person_car_rental();
        break;
      case EVENT_LOAD_PERSON_TERMINAL_1:
        load_person_terminal_1();
        break;
      case EVENT_LOAD_PERSON_TERMINAL_2:
        load_person_terminal_2();
        break;
      case EVENT_LOAD_PERSON_CAR_RENTAL:
        load_person_car_rental();
        break;
    }
	}

  out_timest(stdout, VARIABLE_NQ_TERMINAL_1, VARIABLE_NQ_TERMINAL_1);
	printf("Finish time: %.5f\n", sim_time);
	return 0;
}
