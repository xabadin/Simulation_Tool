#ifndef NODECOUNT_H // include guard
#define NODECOUNT_H

#include "Parameters.h"
#include "Job.h"

/**
*
* The NodeCount class that contains methods needed to keep track
* \n of the supercomputer's allocation of resources
*/
class NodeCount
{
private:
	unsigned int jobID;
	unsigned int hugeNodesNum;
	unsigned int largeNodesNum;
	unsigned int mediumNodesNum;
	unsigned int shortNodesNum;
	unsigned int GPUNodesNum;
	unsigned int time;
	bool isStart;
public:
	// CONSTRUCTORS

	/**
	* Default constructor. Initialize a Node object
	* @param parameters Pointer to Parameters object needed to initialiaze the NodeCount object
	* @param job Job used to initialize the NodeCount
	* @param isStart Defines wether NodeCount is a start or an end of a job
	* @param jobID Job id
	*/
	NodeCount(Parameters* parameters, Job job, bool isStart, unsigned int jobID);

	/**
	* Copy constructor. Build a Node object
	* @param &nodeCount Adress of an existing NodeCount object
	* @param job Job used to initialize the NodeCount
	* @param isStart Defines wether NodeCount is a start or an end of a job
	* @param jobID Job id
	*/
	NodeCount(NodeCount &nodeCount, Job job, bool isStart, unsigned int jobID);

	/**
	* Normal public get method.
	* Get the number of huge nodes available to use
	* @return unsigned int. Number of huge nodes available
	*/
	unsigned int getHugeNodesNum();

	/**
	* Normal public get method.
	* Get the number of large nodes available to use
	* @return unsigned int. Number of large nodes available
	*/
	unsigned int getLargeNodesNum();

	/**
	* Normal public get method.
	* Get the number of medium nodes available to use
	* @return unsigned int. Number of medium nodes available
	*/
	unsigned int getMediumNodesNum();

	/**
	* Normal public get method.
	* Get the number of short nodes available to use
	* @return unsigned int. Number of short nodes available
	*/
	unsigned int getShortNodesNum();

	/**
	* Normal public get method.
	* Get the number of GPU nodes available to use
	* @return unsigned int. Number of GPU nodes available
	*/
	unsigned int getGPUNodesNum();

	/**
	* Normal public get method.
	* Get the time when NodeCount was initialized
	* @return unsigned int. Time of NodeCount initialization
	*/
	unsigned int getTime();

	/**
	* Refreshe the value of the NodeCount when a job is added
	* @param job Job to use in the refresh
	*/
	void refreshNodeCount(Job job);
	
	/**
	* Normal public get method.
	* Check if the NodeCount is a start of a job or an end of a job
	* @return bool. True if NodeCount is a start of a job, else either
	*/
	bool getIsStart();

	/**
	* Normal public get method.
	* Get the id of the job used to initialize the NodeCount
	* @return unsigned int. Job id
	*/
	unsigned int getJobID();
};
#endif;