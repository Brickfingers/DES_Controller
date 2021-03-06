/**
 * Nick Wright & Kevin Luu
 * 040911884 & 040905303
 * CST8244
 */

#ifndef DOOR_ENTRY_SYSTEM_H_
#define DOOR_ENTRY_SYSTEM_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/neutrino.h>
#include <sys/netmgr.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/neutrino.h>
#include <limits.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#define NUM_STATES 13	// where n = number of states in your finite state machine (FSM)
#define NUM_INPUTS 12	// where n equals the number of input commands that drive the FSM.
//From the assignment specification, notice the prompt.
//Each command, ls, rs, etc.

typedef enum State{
	//assign an enum value, one for each state
	IDLE_STATE = 0,
    LEFT_SCAN_STATE = 1,
    RIGHT_SCAN_STATE = 2,
    GUARD_LEFT_UNLOCK_STATE = 3,
    GUARD_RIGHT_UNLOCK_STATE = 4,
    LEFT_OPEN_STATE = 5,
    RIGHT_OPEN_STATE = 6,
    WEIGHT_SCALE_STATE = 7,
    LEFT_CLOSED_STATE = 8,
    RIGHT_CLOSED_STATE = 9,
    GUARD_LEFT_LOCK_STATE = 10,
    GUARD_RIGHT_LOCK_STATE = 11,
	EXIT_STATE = 12
} State;

typedef enum {
	IN = 0,
	OUT = 1
} Direction;

typedef enum {
	//assign an enum value, one for each input command
	LS = 0,
	RS = 1,
	GLU = 2,
	GRU = 3,
	LO = 4,
	RO = 5,
	WS = 6,
	LC = 7,
	RC = 8,
	GLL = 9,
	GRL = 10,
	EX = 11
} Input;

const char *inMessage[NUM_INPUTS] = {
	//each input command. For example, "ls"
	"ls",
	"rs",
	"glu",
	"gru",
	"lo",
	"ro",
	"ws",
	"lc",
	"rc",
	"gll",
	"grl",
	"exit"
};

#define NUM_OUTPUTS 11	// where n equals the number of output messages from the FSM.
typedef enum {
	//assign an enum value, one for each output message from the FSM
	ID_SCANNED = 0,
	GUARD_LEFT_UNLOCK = 1,
	GUARD_RIGHT_UNLOCK = 2,
	LEFT_OPEN = 3,
	RIGHT_OPEN = 4,
	WEIGHED = 5,
	LEFT_CLOSE = 6,
	RIGHT_CLOSE = 7,
	GUARD_LEFT_LOCK = 8,
	GUARD_RIGHT_LOCK = 9,
	EXIT = 10
} Output;

const char *outMessage[NUM_OUTPUTS] = {
	//each output message. For example, "Person opened left door"
    "Person scanned ID, ID: =",
    "Guard left door unlocked.",
    "Guard right door unlocked.",
    "Person opened left door",
    "Person opened right door.",
    "Person weighed, weight =",
    "Left door closed (Automatically)",
    "Right door closed (Automatically)",
    "Guard left door locked.",
    "Guard right door locked.",
    "Exiting"
};

// inputs client sends a Person struct to its server, the controller
typedef struct {
	//TODO :: fields for person's ID (int), weight (int),
	//direction (inbound or outbound), and some way to remember
	//what state the Person is in. Suppose the Person in
	//"Left Scan" state. You need a way to represent that.
	int id;
	char* input;
	int weight;
	Direction direction;
	State state;
} Person;

// controller client sends a Display struct to its server, the display
typedef struct {
	//fields for the output message and the Person.
	//For the output message, I used an int, which is the index
	//into the outMessages array. That way I don't pass strings
	//in my messages. The Person field is needed, as some output
	//message require information from the Person. Specifically,
	//those messages that display the Person's ID and weight.
	Output output;
	Person person;
} Display;

int* idle_handler(int coid, Person* person, Output* output);
int* left_scan_handler(int coid, Person* person, Output* output);
int* right_scan_handler(int coid, Person* person, Output* output);
int* guard_left_unlock_handler(int coid, Person* person, Output* output);
int* guard_right_unlock_handler(int coid, Person* person, Output* output);
int* open_left_handler(int coid, Person* person, Output* output);
int* open_right_handler(int coid, Person* person, Output* output);
int* weight_handler(int coid, Person* person, Output* output);
int* left_close_handler(int coid, Person* person, Output* output);
int* right_close_handler(int coid, Person* person, Output* output);
int* guard_left_lock_handler(int coid, Person* person, Output* output);
int* guard_right_lock_handler(int coid, Person* person, Output* output);
int* exit_handler(int coid, Person* person, Output* output);

#endif /* DOOR_ENTRY_SYSTEM_H_ */
