#ifndef SIMULATION_H // include guard
#define SIMULATION_H

#include <vector>
#include <random>
#include <ctime>
#include "NodeCount.h"
#include "User.h"
#include "UserType.h"
#include "UserType.h"
#include "Parameters.h"
#include "Job.h"

/**
*
* The Simulation class that contains methods needed
* \n to run the whole simulation
*/
class Simulation : Data
{
private:
	std::vector<Job*> jobs;
	std::vector<User*>  users;
	std::vector<NodeCount> nodeCounts;
	Parameters* parameters;
public:

	// CONSTRUCTORS

	/**
	* Default constructor. Intialize a Simulation object
	* @param parameters Pointer to parameters object needed to initialiaze the NodeCount object
	*/
	Simulation(Parameters* parameters);

	/**
	* Fill the jobs vector with random Job objects
	* @see std::vector<Job*> getVecJobs()
	*/
	void fillVecJobs();

	/**
	* Fill the users vector with random User objects
	* std::vector<Job*> getVecUsers()
	*/
	void fillVecUsers();

	/**
	* Generate a random number between min and max parameters
	* @see double exponentialDistribution(double lambda)
	* @see double normalDistribution(double mean, double stdDeviation)
	* @param min
	* @param max
	* @return int. Random number
	*/
	int randomNumGenerator(int min, int max);

	/**
	* Generate a random number following an exponential distribution based on given lambda
	* @see int randomNumGenerator(int min, int max)
	* @see double normalDistribution(double mean, double stdDeviation)
	* @param lambda
	* @return double. Random number
	*/
	double exponentialDistribution(double lambda);

	/**
	* Generate a random number following an exponential distribution based on given mean and deviation
	* @see int randomNumGenerator(int min, int max)
	* @see double exponentialDistribution(double lambda)
	* @param mean
	* @param stdDeviation
	* @return double. Random number
	*/
	double normalDistribution(double mean, double stdDeviation);

	/**
	* Scheduler method following a first-come first-served rule
	*/
	void scheduler();

	/**
	* Check if the given time is during the week-end or not
	* @param submissionTime
	* @return bool. True if submissionTime is during a week-end, false either
	*/
	bool weekEnd(unsigned int submissionTime);

	/**
	* Give the index of the next NodeCount in the nodecount vector (the next NodeCount with the time given)
	* @param time
	* @param j
	* @return int. Index of the next NodeCount in the nodecount vector
	*/
	int findNext(unsigned int time, int j);

	/**
	* Find when there are enough ressources to start a job
	* @param &indexNodeCount
	* @param job Job to check the ressources for
	* @param &time Current time
	*/
	void startJob(int& indexNodeCount, Job job, unsigned int& time);

	/**
	* Check if there is enough ressource long enough in the queue to run the job
	* @param time Current time
	* @param job Job to check the ressources for
	* @param &indexNodeCount
	* @return bool. True if enough ressources, false either
	*/
	bool enoughTime(unsigned int time, Job job, int& indexNodeCount);

	/**
	* Check if there is space available in the queue at a specific NodeCount
	* @param job Job to check the space for
	* @param nodeCount NodeCount to check the space at
	* @return bool. True if enough space, false either
	*/
	bool isSpaceAvailable(Job job, NodeCount nodeCount);

	/**
	* Give the starting time of next week
	* @param time Current time
	* @return unsigned int. Next week's start time
	*/
	unsigned int nextWeek(unsigned int time);

	/**
	* Submits the start and end NodeCounts in the NodeCount vector + sets start and end time of the job
	* \n + refreshes the node count vector if needed + sorts the nodecount vector after submission
	* @param time Current time
	* @param &job
	* @param indexNodeCount
	* @param ID
	*/
	void submitNodeCount(unsigned int time, Job& job, int indexNodeCount, unsigned int ID);

	/**
	* Normal public get method.
	* Get the vector of all the Job objects created in the simulation
	* @see void fillVecJobs()
	* @return std::vector<Job*>. Vector of jobs in simulation
	*/
	std::vector<Job*> getVecJobs();

	/**
	* Normal public get method.
	* Get the vector of all the User objects created in the simulation
	* @see void fillVecUsers()
	* @return std::vector<User*>. Vector of users in simulation
	*/
	std::vector<User*> getVecUsers();

	/**
	* Normal public get method.
	* Get the vector of all the NodeCount objects created in the simulation
	* @return std::vector<NodeCount>. Vector of nodecounts in simulation
	*/
	std::vector<NodeCount> getVecNodeCounts();

	/**
	* Finds when there are enough ressources to run a huge job
	* Get the vector of all the NodeCount objects created in the simulation
	* @param &indexNodeCount
	* @param job Job to check the ressources for
	* @param &time Current time
	*/
	void startHugeJob(int& indexNodeCount, Job job, unsigned int& time);

	/**
	* Give the starting time of next week-end
	* @param time Current time
	* @return unsigned int. Next week-end's start time
	*/
	unsigned int nextWeekEnd(unsigned int time);

	/**
	* Check if a nodecount (start or end) exists at a given time
	* @param time Time to check the existence of the NodeCount
	* @return bool. True if it exists, false either
	*/
	bool nodeCountExists(unsigned int& time);
};
#endif;
