#include "Simulation.h"
#include <fstream>

//Alternate constructor
Simulation::Simulation(Parameters* parameters)
{
	this->parameters = parameters;
	fillVecUsers();
	fillVecJobs();
	//sort the jobs vector with the submission time
	std::sort(jobs.begin(), jobs.end(), [](Job* job1, Job* job2) {return job1->getSubmissionTime() < job2->getSubmissionTime(); });
	scheduler();
}

//Randomly generates the users and inserts them in a vector. The percentage of generated users is assumed to be approximately 10/16 students, 5/16 researchers and 1/16 IT staff.
void Simulation::fillVecUsers()
{
	// Creates users, IT users are created with an unlimited budget.
	for (unsigned int i = 0; i < parameters->getNumberOfUsers(); ++i)
	{
		int randomNumber = randomNumGenerator(0, 15);
		if (randomNumber >= 0 && randomNumber <= 9)
		{
			User* user = new User(i, UserType::Student, parameters->getStudentBudget(), parameters->getStudentMaxNodes());
			this->users.push_back(user);
		}
		else if (randomNumber >= 10 && randomNumber <= 14)
		{
			User* user = new User(i, UserType::Researcher, parameters->getResearcherBudget(), parameters->getResearcherMaxNodes());
			this->users.push_back(user);
		}
		// We decided that IT Staff wouldn't send any job requests, which explains the 0 as the 3rd 
		// parameter of the following User constructor
		else
		{
			User* user = new User(i, UserType::IT, 0, parameters->getNumberOfNodes());
			this->users.push_back(user);
		}
	}
}

void Simulation::fillVecJobs()
{
	for (unsigned int i = 0; i < parameters->getNumberOfJobs(); ++i)
	{
		bool isGPUJob = false;
		unsigned int nodesRequired = 0;
		unsigned int jobDuration = 0;
		//Generates a random number to distribute the jobs according to the assumed ratio in the requirements.
		//Following a normal distribution gives the number of nodes and the duration time of the job according to the queue
		int randomNumber = randomNumGenerator(0, 99);
		if (randomNumber >= 0 && randomNumber <= 69)
		{
			//Creates short jobs (2 nodes max and up to two hours)
			while (nodesRequired <= 0 || nodesRequired > 2 || jobDuration <= 0 || jobDuration > ONE_HOUR_IN_SEC * 2)
			{
				nodesRequired = (int)normalDistribution(1.5, 0.5);
				jobDuration = (int)normalDistribution(ONE_HOUR_IN_SEC, 1000.0);
			}
		}
		else if (randomNumber >= 70 && randomNumber <= 84)
		{
			//Creates medium jobs (10% of total number of nodes max and up to 8 hours)
			while (nodesRequired <= 0 || nodesRequired >= parameters->getNumberOfMediumNodes() || jobDuration <= ONE_HOUR_IN_SEC * 2 || jobDuration > EIGHT_HOURS_IN_SEC)
			{
				//The mean of the normal distribution is 5% of the total node count
				nodesRequired = (int)normalDistribution((double)parameters->getNumberOfMediumNodes() / 2.0, 3.0);
				jobDuration = (int)normalDistribution(EIGHT_HOURS_IN_SEC / 2, 7000.0);
			}
		}
		else if (randomNumber >= 85 && randomNumber <= 89)
		{
			//Creates large jobs (50% of total number of nodes max and up to 16 hours)
			while (nodesRequired <= 0 || nodesRequired >= parameters->getNumberOfLargeNodes() || jobDuration <= EIGHT_HOURS_IN_SEC || jobDuration > SIXTEEN_HOURS_IN_SEC)
			{
				//The mean of the normal distribution is 25% of the total node count
				nodesRequired = (int)normalDistribution((double)parameters->getNumberOfLargeNodes() / 2.0, 15.0);
				jobDuration = (int)normalDistribution(ONE_HOUR_IN_SEC * 12, 7000.0);
			}
		}
		else if (randomNumber >= 90 && randomNumber <= 98)
		{
			isGPUJob = true;
			//Creates GPU jobs (8 nodes max and up to 16 hours)
			while (nodesRequired <= 0 || nodesRequired >= parameters->getNumberOfGPUNodes() || jobDuration <= 0 || jobDuration > SIXTEEN_HOURS_IN_SEC)
			{
				//The mean of the normal distribution is half the number of GPU nodes
				nodesRequired = (int)normalDistribution((double)parameters->getNumberOfGPUNodes() / 2.0, 2.0);
				jobDuration = (int)normalDistribution(ONE_HOUR_IN_SEC * 4.0, 7000.0);
			}
		}
		else
		{
			//Creates huge jobs (More than 16 hours and more than 50% of the node count)
			while (nodesRequired < parameters->getNumberOfLargeNodes() || nodesRequired > parameters->getNumberOfHugeNodes() || jobDuration <= SIXTEEN_HOURS_IN_SEC || jobDuration > SIXTY_FOUR_HOURS_IN_SEC)
			{
				//The mean of the normal distribution is : (number of nodes - GPU nodes - 50% of the node count) / 2) + 50 % of the node count
				nodesRequired = (int)normalDistribution((((double)parameters->getNumberOfHugeNodes() - (double)parameters->getNumberOfLargeNodes()) / 2.0) + (double)parameters->getNumberOfLargeNodes(), 15.0);
				jobDuration = (int)normalDistribution(60.0 * 60.0 * 64.0 / 2, 50000.0);
			}
		}

		//I need to choose a correct value for the exponential distribution (0.0000016 gives an average of a week)
		double lambda = 0.0000016;
		unsigned int submissionTime = (unsigned int)exponentialDistribution(lambda);
		Job* job = new Job(submissionTime, jobDuration, nodesRequired, isGPUJob);
		int index = 0;
		//IT users can't submit jobs
		while (index < users.size() && users[index]->getType() == UserType::IT || !users[index]->checkBudget(job) || !users[index]->checkNumMaxNodes(job))
		{
			index++;
			if (index >= users.size()) {
				break;
			}
		}
		if (index < users.size()) {
			job->setUser(users[index]);
			users[index]->decreaseBudget(job);
			jobs.push_back(job);
		}
	}
}

void Simulation::scheduler()
{
	for (int i = 0; i < jobs.size(); ++i)
	{
		unsigned int j = 0;
		unsigned int time = jobs[i]->getSubmissionTime();
		if (jobs[i]->isHugeJob())
		{
			//Assigns the huge jobs
			int indexNodeCount = findNext(time, j);
			startHugeJob(indexNodeCount, *jobs[i], time);
			submitNodeCount(time, *jobs[i], indexNodeCount, i);
		}
		else
		{
			//Assigns the large, GPU, medium and short jobs
			int indexNodeCount = findNext(time, j);
			if (indexNodeCount != nodeCounts.size())
			{
				startJob(indexNodeCount, *jobs[i], time);
				while (!enoughTime(time, *jobs[i], indexNodeCount))
				{
					startJob(indexNodeCount, *jobs[i], time);
				}
			}
			submitNodeCount(time, *jobs[i], indexNodeCount, i);
		}
	}
}

unsigned int Simulation::nextWeekEnd(unsigned int time)
{
	if (time < WEEKEND_START_IN_SEC)
	{
		time = WEEKEND_START_IN_SEC;
	}
	else
	{
		int quotient = time / WEEK_START_IN_SEC;
		time = (quotient + 1) * WEEK_START_IN_SEC + WEEKEND_START_IN_SEC;
	}
	return time;
}

// Refreshes the value of the nodecounts impacted by the job and Inserts the node count into the nodecount vector, and then sorts the vector nodecount with the time parameter
void Simulation::submitNodeCount(unsigned int time, Job& job, int indexNodeCount, unsigned int jobID)
{
	job.setStartTime(time);
	job.setEndTime(time + job.getJobDuration());
	//Refresh values
	int endIndex = indexNodeCount;
	bool isRefresh = false;
	//this while is not working never going in it (hence, never refreshing the values)
	unsigned int endTime = time + job.getJobDuration();
	while (endIndex < nodeCounts.size() && nodeCounts[endIndex].getTime() < endTime && isSpaceAvailable(job, nodeCounts[endIndex]))
	{
		isRefresh = true;
		nodeCounts[endIndex].refreshNodeCount(job);
		endIndex++;
	}
	//creates Nodecounts
	if (indexNodeCount == 0)
	{
		NodeCount* startNodeCount = new NodeCount(parameters, job, true, jobID);
		NodeCount* endNodeCount = new NodeCount(*startNodeCount, job, false, jobID);
		nodeCounts.push_back(*startNodeCount);
		nodeCounts.push_back(*endNodeCount);
	}
	else if (job.isHugeJob())
	{
		NodeCount* startNodeCount = new NodeCount(nodeCounts[indexNodeCount - 1], job, true, jobID);
		NodeCount* endNodeCount = new NodeCount(*startNodeCount, job, false, jobID);
		nodeCounts.push_back(*startNodeCount);
		nodeCounts.push_back(*endNodeCount);
	}
	else
	{
		NodeCount* startNodeCount = new NodeCount(nodeCounts[indexNodeCount - 1], job, true, jobID);
		if (!isRefresh)
		{
			NodeCount* endNodeCount = new NodeCount(*startNodeCount, job, false, jobID);
			nodeCounts.push_back(*endNodeCount);
		}
		else {
			NodeCount* endNodeCount = new NodeCount(nodeCounts[endIndex - 1], job, false, jobID);
			nodeCounts.push_back(*endNodeCount);
		}
		nodeCounts.push_back(*startNodeCount);
	}

	std::sort(nodeCounts.begin(), nodeCounts.end(), [](NodeCount nodeCount1, NodeCount nodeCount2) {return nodeCount1.getTime() < nodeCount2.getTime(); });
}

//Checks if there are enough ressources long enoug in the queue to compute this job
bool Simulation::enoughTime(unsigned int time, Job job, int& indexNodeCount)
{
	int i = indexNodeCount;
	int j = i;
	bool enoughTime = false;
	unsigned int endTime = time + job.getJobDuration();
	while (i < nodeCounts.size() && nodeCounts[i].getTime() <= endTime)
	{
		if (isSpaceAvailable(job, nodeCounts[i]))
		{
			j++;
		}
		i++;
	}
	if (nodeCounts.size() == j || nodeCounts[j].getTime() > job.getJobDuration() + time)
	{
		enoughTime = true;
	}
	else {
		indexNodeCount++;
	}
	return enoughTime;
}

//checks if there are enough nodes to run the given job
bool Simulation::isSpaceAvailable(Job job, NodeCount nodeCount)
{
	int availableNodes = 0;
	if (job.isGPUJob())
	{
		availableNodes = nodeCount.getGPUNodesNum() - job.getNodesRequired();
	}
	else if (job.isLargeJob()) {
		availableNodes = nodeCount.getLargeNodesNum() - job.getNodesRequired();
	}
	else if (job.isMediumJob()) {
		availableNodes = nodeCount.getMediumNodesNum() - job.getNodesRequired();
	}
	else if (job.isShortJob()) {
		availableNodes = nodeCount.getShortNodesNum() - job.getNodesRequired();
	}
	else if (job.isHugeJob())
	{
		availableNodes = nodeCount.getHugeNodesNum() - job.getNodesRequired();
	}
	return availableNodes >= 0;
}

//Used to find the index of the next NodeCount in the vector (which is starting just after the given time)
int Simulation::findNext(unsigned int time, int j)
{
	while (j < nodeCounts.size() && nodeCounts[j].getTime() <= time)
	{
		j++;
	}
	return j;
}

//Finds when there are enough available nodes to start the job
void Simulation::startJob(int& indexNodeCount, Job job, unsigned int& time)
{
	int j = indexNodeCount;
	while (j != 0 && j - 1 < nodeCounts.size() && !isSpaceAvailable(job, nodeCounts[j - 1]))
	{
		j++;
		time = nodeCounts[j - 1].getTime();
	}
	if (weekEnd(time + job.getJobDuration()))
	{
		time = nextWeek(time);
		j = findNext(time, j);
		startJob(j, job, time);
	}
	if (j != 0 && j != nodeCounts.size())
	{
		if (nodeCountExists(time))
		{
			time++;
			j = findNext(time, j);
			startJob(j, job, time);
		}
	}
	indexNodeCount = j;
}

//Recursive method
void Simulation::startHugeJob(int& indexNodeCount, Job job, unsigned int& time)
{
	int j = indexNodeCount;
	time = nextWeekEnd(time);
	j = findNext(time, j);
	while (j != 0 && j - 1 < nodeCounts.size() && !isSpaceAvailable(job, nodeCounts[j - 1]))
	{
		j++;
		time = nodeCounts[j - 1].getTime();
	}
	if (!weekEnd(time + job.getJobDuration()))
	{
		time = nextWeekEnd(time);
		j = findNext(time, j);
		startHugeJob(j, job, time);
	}
	if (j != 0 && j != nodeCounts.size())
	{
		if (nodeCountExists(time))
		{
			time++;
			j = findNext(time, j);
			startHugeJob(j, job, time);
		}
	}
	indexNodeCount = j;
}

bool Simulation::nodeCountExists(unsigned int& time)
{
	bool nodeCountExists = false;

	for (unsigned int i = 0; i < nodeCounts.size(); ++i)
	{
		if (nodeCounts[i].getTime() == time)
		{
			nodeCountExists = true;
		}
	}
	return nodeCountExists;
}
//Takes the time and returns the time in seconds the next monday at 9 am
unsigned int Simulation::nextWeek(unsigned int time)
{
	if (time < WEEK_START_IN_SEC)
	{
		time = WEEK_START_IN_SEC;
	}
	else
	{
		int quotient = time / WEEK_START_IN_SEC;
		time = (quotient + 1) * WEEK_START_IN_SEC;
	}
	return time;
}

//Checks if the given time is during the weekend
bool Simulation::weekEnd(unsigned int time)
{
	bool weekEnd = false;
	time = time % WEEK_START_IN_SEC;
	if (time >= (unsigned int)WEEKEND_START_IN_SEC && time <= (unsigned int)WEEK_START_IN_SEC)
	{
		weekEnd = true;
	}
	return weekEnd;
}

int Simulation::randomNumGenerator(int min, int max)
{
	int randomNumber = 0;
	std::random_device random; // It is used to obtain a seed to generate random numbers
	std::mt19937 generator(random());
	std::uniform_int_distribution<> distrib(min, max);
	randomNumber = distrib(generator);
	return randomNumber;
}

double Simulation::exponentialDistribution(double lambda)
{
	std::random_device random; // It is used to obtain a seed to generate random numbers
	std::mt19937 generator(random());
	std::exponential_distribution<double> expDistribution(lambda);
	return expDistribution(generator);
}

double Simulation::normalDistribution(double mean, double stdDeviation)
{
	double randomNumber = 0.0;
	std::random_device random; // It is used to obtain a seed to generate random numbers
	std::mt19937 generator(random());
	std::normal_distribution<double> distribution(mean, stdDeviation);
	return distribution(generator);
}

std::vector<Job*> Simulation::getVecJobs()
{
	return this->jobs;
}

std::vector<User*> Simulation::getVecUsers()
{
	return this->users;
}

std::vector<NodeCount> Simulation::getVecNodeCounts()
{
	return this->nodeCounts;
}
