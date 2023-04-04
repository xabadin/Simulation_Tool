#ifndef Data_H // include guard
#define Data_H

class Data {
public:
	// minimun and maximun number of nodes
	const int MIN_NUMBER_OF_NODES = 128;
	const int MAX_NUMBER_OF_NODES = 512;

	const int NUMBER_OF_GPU_NODES = 8;

	// minimun and maximun number of users
	//const int MIN_NUMBER_OF_USERS = 1;
	//const int MAX_NUMBER_OF_USERS = 3000;
	const int MIN_NUMBER_OF_USERS = 10;
	const int MAX_NUMBER_OF_USERS = 1000;
	const int NUMBER_OF_USERS = 200;

	// budget
	const int STUDENT_BUDGET = 500;
	const int RESEARCHER_BUDGET = 1000;

	// maximum number of nodes that can be requested simultaneously
	const int STUDENT_MAX_NODES = 16;
	const int RESEARCHER_MAX_NODES = 128;

	// Usage cost with the traditional node-hour cost and the accelerated node-hour cost. They are divided by 3600 to express them in seconds.
	const double TRADITIONAL_NODE_COST = 0.10 / 3600;
	const double ACCELERATED_NODE_COST = 0.20 / 3600;

	// The operating cost is calculated with different variables, it expresses the operating cost of the system per second. The calculation method is explained in the report.
	const double OPERATING_COST = 0.0127;

	// minimun and maximun number of jobs to run
	const int MIN_NUMBER_OF_JOBS = 10;
	const int MAX_NUMBER_OF_JOBS = 500;
	const int NUMBER_OF_JOBS = 300;

	const unsigned int ONE_HOUR_IN_SEC = 60 * 60; // One hour in seconds
	const unsigned int EIGHT_HOURS_IN_SEC = 8 * ONE_HOUR_IN_SEC; // Eight hours in seconds
	const unsigned int SIXTEEN_HOURS_IN_SEC = 2 * EIGHT_HOURS_IN_SEC; // Sixteen hours in seconds
	const unsigned int ONE_DAY_IN_SEC = 3 * EIGHT_HOURS_IN_SEC; // One day in seconds
	const unsigned int SIXTY_FOUR_HOURS_IN_SEC = 8 * EIGHT_HOURS_IN_SEC; // Sixty four hours in seconds


	// start time of the weekend in sec assuming that each simulation starts a monday at midnight. Week end starts Friday at 5 pm.
	const unsigned int WEEKEND_START_IN_SEC = 4 * ONE_DAY_IN_SEC + 17 * ONE_HOUR_IN_SEC;
	const unsigned int WEEK_START_IN_SEC = 7 * ONE_DAY_IN_SEC + 9 * ONE_HOUR_IN_SEC; // One week in seconds
};
#endif