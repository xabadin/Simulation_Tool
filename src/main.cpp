#include <iostream>
#include <filesystem>
#include <vector>
#include <fstream>
#include <cmath>
#include "float.h"
#include "Simulation.h"
#include "Parameters.h"

std::vector<double> input();
double checkInput(double input, double min = 0.0, double max = DBL_MAX);
void clearInput();
void outputNodeCountsCsv(Simulation* simulation);
void outputJobsCsv(Simulation* simulation);
std::vector<int> computeNumberOfJobsInEachQueue(Simulation* simulation);
double computeNumberOfNodeHoursConsumed(Simulation* simulation);
double computeUtilizationRatio(Simulation* simulation, double numberOfNodesInput);
double computeTotalPricePaidByUsers(Simulation* simulation);
std::vector<long double> computeAvgWaitTimeInEachQueue(Simulation* simulation);
double computeAvgTurnAroundTimeRatio(Simulation* simulation);
double computeEconomicBalanceOfCentre(Simulation* simulation);
void createOutputsDirectory();

/*
  Used to create the simulation for the IT staff
*/
int main() {
	// Time is set to t = 0 because it is assumed that each simulation starts a monday at midnight. 
	unsigned int time = 0;

	// ask user for his input
	std::vector<double> param = input();
	Parameters* parameters = new Parameters(param[0], param[1], param[2], param[3], param[4], param[5], param[6], param[7], param[8]);
	// run the simulation
	Simulation* simulation = new Simulation(parameters);

	// Create the outputs directory
	createOutputsDirectory();
	// Create and fill csv files with the different allocation of ressources throughout the simulation
	outputNodeCountsCsv(simulation);
	// Create and fill csv files with the different jobs created throughout the simulation
	outputJobsCsv(simulation);

	// Creation of the file receiving the required outputs
	std::ofstream Outputs("outputs/Outputs.csv");

	Outputs << "Queue;Short;Medium;Large;Huge;GPU" << std::endl;

	// Output of the number of jobs processed in each queue
	int numjobsShort, numjobsMedium, numjobsLarge, numjobsHuge, numjobsGPU;
	std::vector<int> numJobs = computeNumberOfJobsInEachQueue(simulation);
	Outputs << "Number of jobs processed;" << numJobs[0] << ";" << numJobs[1] << ";" << numJobs[2] << ";" << numJobs[3] << ";" << numJobs[4] << std::endl;

	// Output of the average wait time in each queue
	int avgShort, avgMedium, avgLarge, avgHuge, avgGPU;
	std::vector<long double> avgWaitTime = computeAvgWaitTimeInEachQueue(simulation);
	Outputs << "Average wait time (h);" << avgWaitTime[0] << ";" << avgWaitTime[1] << ";" << avgWaitTime[2] << ";" << avgWaitTime[3] << ";" << avgWaitTime[4] << std::endl << std::endl;
	Outputs << "Number of node-hours consumed by user jobs;Utilization ratio;Resulting price paid by the users;Average turnaround time ratio;Economic balance of the centre" << std::endl;

	// Computing of the actual number of node-hours consumed by user jobs
	double totalNumberOfNodeHoursConsumed = computeNumberOfNodeHoursConsumed(simulation);
	// Computing of the utilisation ratio
	// Not working
	double utilizationRatio = computeUtilizationRatio(simulation, param[2]);
	// Computing of the resulting price paid by the users
	double resultingPricePaidByUsers = computeTotalPricePaidByUsers(simulation);
	// Computing of the average turnaround time ratio
	// Problem with result
	double avgTurnAroundTimeRatio = computeAvgTurnAroundTimeRatio(simulation);
	// Computing of the economic balance of the centre
	double economicBalanceOfCentre = computeEconomicBalanceOfCentre(simulation);

	Outputs << totalNumberOfNodeHoursConsumed << ";" << utilizationRatio << ";" << resultingPricePaidByUsers << " £;" << avgTurnAroundTimeRatio << ";" << economicBalanceOfCentre << " £";

	std::cout << "Simulation complete" << std::endl;
	std::cout << "You will find the outputs of the simulation in the Outputs directory" << std::endl;

	return 0;
}

std::vector<double> input() {
	Data data;
	std::vector<double> inputs;
	double input = 0;

	std::cout << "Welcome to the supercomputer simulation software" << std::endl;
	std::cout << "Before running the simulation, you are able to set different parameters to fit your need" << std::endl;
	std::cout << "Be careful, if the values you enter are absurd, you will get absurd results" << std::endl << std::endl;

	// Number of users
	std::cout << "The first parameter is the number of users that will be sending job requests to your supercomputer" << std::endl;
	std::cout << "The minimum being " << data.MIN_NUMBER_OF_USERS << " and the maximum value " << data.MAX_NUMBER_OF_USERS << std::endl;
	std::cout << "The default value is " << data.NUMBER_OF_USERS << std::endl;
	std::cout << "If you wish to keep this value, type 0, otherwise, enter the number of users you want: " << std::endl;
	double numberofUsers = checkInput(input, data.MIN_NUMBER_OF_USERS, data.MAX_NUMBER_OF_USERS);
	inputs.push_back(numberofUsers);

	// Number of jobs
	std::cout << "The second parameter is the total number of jobs that will be sent by users throughout the simulation" << std::endl;
	std::cout << "The minimum being " << data.MIN_NUMBER_OF_JOBS << " and the maximum value " << data.MAX_NUMBER_OF_JOBS << std::endl;
	std::cout << "The default value is " << data.NUMBER_OF_JOBS << std::endl;
	std::cout << "If you wish to keep this value, type 0, otherwise, enter the number of jobs you want: " << std::endl;
	double numberOfJobs = checkInput(input, data.MIN_NUMBER_OF_JOBS, data.MAX_NUMBER_OF_JOBS);
	inputs.push_back(numberOfJobs);

	// Number of nodes
	std::cout << "The third parameter is the total number of nodes that the supercomputer will be able to use to run the jobs" << std::endl;
	std::cout << "The minimum being " << data.MIN_NUMBER_OF_NODES << " and the maximum value " << data.MAX_NUMBER_OF_NODES << std::endl;
	std::cout << "The default value is " << data.MIN_NUMBER_OF_NODES << std::endl;
	std::cout << "If you wish to keep this value, type 0, otherwise, enter the number of nodes you want: " << std::endl;
	double numberOfNodes = checkInput(input, data.MIN_NUMBER_OF_NODES, data.MAX_NUMBER_OF_NODES);
	inputs.push_back(numberOfNodes);

	// Traditional node cost
	std::cout << "Knowing that the supercomputer uses traditional nodes and accelerated nodes, " << std::endl;
	std::cout << "The fourth parameter is the cost (per hour) of a traditional node" << std::endl;
	std::cout << "The default value is " << data.TRADITIONAL_NODE_COST * 3600 << " pounds/h" << std::endl;
	std::cout << "If you wish to keep this value, type 0, otherwise, enter the cost you want: " << std::endl;
	double traditionalNodeCost = checkInput(input);
	inputs.push_back(traditionalNodeCost);

	// Accelerated node cost
	std::cout << "Now the fifth parameter is the cost (per hour) of an accelerated node" << std::endl;
	std::cout << "The default value is " << data.ACCELERATED_NODE_COST * 3600 << " pounds/h" << std::endl;
	std::cout << "If you wish to keep this value, type 0, otherwise, enter the cost you want: " << std::endl;
	double acceleratedNodeCost = checkInput(input);
	inputs.push_back(acceleratedNodeCost);

	// Student budget
	std::cout << "The sixth parameter is the budget allowed to students" << std::endl;
	std::cout << "The default value is " << data.STUDENT_BUDGET << " pounds" << std::endl;
	std::cout << "If you wish to keep this value, type 0, otherwise, enter the cost you want: " << std::endl;
	double studentBudget = checkInput(input);
	inputs.push_back(studentBudget);

	// Student max nodes
	std::cout << "The seventh parameter is the maximum number of nodes students are allowed to use a the same time" << std::endl;
	std::cout << "The default value is " << data.STUDENT_MAX_NODES << " pounds" << std::endl;
	std::cout << "If you wish to keep this value, type 0, otherwise, enter the cost you want: " << std::endl;
	double studentMaxNodes = checkInput(input);
	inputs.push_back(studentMaxNodes);

	// Reasearcher budget
	std::cout << "The eighth parameter is the budget allowed to reasearchers" << std::endl;
	std::cout << "The default value is " << data.RESEARCHER_BUDGET << " pounds" << std::endl;
	std::cout << "If you wish to keep this value, type 0, otherwise, enter the cost you want: " << std::endl;
	double researcherBudget = checkInput(input);
	inputs.push_back(researcherBudget);

	// Reasearcher max nodes
	std::cout << "The last parameter is the maximum number of nodes reasearchers are allowed to use a the same time" << std::endl;
	std::cout << "The default value is " << data.RESEARCHER_MAX_NODES << " pounds" << std::endl;
	std::cout << "If you wish to keep this value, type 0, otherwise, enter the cost you want: " << std::endl;
	double researcherMaxNodes = checkInput(input);
	inputs.push_back(researcherMaxNodes);

	return inputs;

}

double checkInput(double input, double min, double max) {
	if (std::cin >> input) {
		if (input == 0) {
			std::cout << std::endl << std::endl;
			return input;
		}
		if (min != 0.0 || max != DBL_MAX) {
			if (input >= min && input <= max) {
				std::cout << std::endl << std::endl;
				return input;
			}
			else {
				std::cout << "Invalid Input! Please input a value that respects the min (" << min << ") and max (" << max << ") boundaries ." << std::endl;
				clearInput();
				double newInput = 0;
				return checkInput(newInput, min, max);
			}
		}
		else {
			if (input >= 0) {
				std::cout << std::endl << std::endl;
				return input;
			}
			else {
				std::cout << "Invalid Input! Please input a positive value." << std::endl;
				clearInput();
				double newInput = 0;
				return checkInput(newInput);
			}
		}
	}
	else {

		std::cout << "Invalid Input! Please input a numerical value." << std::endl;
		clearInput();
		double newInput = 0;
		if (min != 0.0 || max != DBL_MAX) {
			return checkInput(newInput, min, max);
		}
		else {
			return checkInput(newInput);
		}
	}
}

void clearInput() {
	std::cin.clear();
	while (std::cin.get() != '\n');
}

void outputNodeCountsCsv(Simulation* simulation) {
	std::ofstream NodeCounts("outputs/Nodecounts.csv");
	NodeCounts << "Time;Huge;GPU;Large;Medium;Short;isStart;ID" << std::endl;
	for (int i = 0; i < simulation->getVecNodeCounts().size(); ++i)
	{
		NodeCounts << simulation->getVecNodeCounts()[i].getTime() << ";" << simulation->getVecNodeCounts()[i].getHugeNodesNum() << ";" << simulation->getVecNodeCounts()[i].getGPUNodesNum() << ";" << simulation->getVecNodeCounts()[i].getLargeNodesNum() << ";" << simulation->getVecNodeCounts()[i].getMediumNodesNum() << ";" << simulation->getVecNodeCounts()[i].getShortNodesNum() << ";" << simulation->getVecNodeCounts()[i].getIsStart() << ";" << simulation->getVecNodeCounts()[i].getJobID() << std::endl;
	}
}

void outputJobsCsv(Simulation* simulation) {
	std::ofstream jobs("outputs/Jobs.csv");
	jobs << "ID;submissionTime;duration;startTime;endTime;nodesRequired" << std::endl;
	for (int i = 0; i < simulation->getVecJobs().size(); ++i)
	{
		jobs << i << ";" << simulation->getVecJobs()[i]->getSubmissionTime() << ";" << simulation->getVecJobs()[i]->getJobDuration() << ";" << simulation->getVecJobs()[i]->getStartTime() << ";" << simulation->getVecJobs()[i]->getEndTime() << ";" << simulation->getVecJobs()[i]->getNodesRequired() << std::endl;
	}
}

std::vector<int> computeNumberOfJobsInEachQueue(Simulation* simulation) {
	int numShort, numMedium, numLarge, numHuge, numGPU;
	numShort = numMedium = numLarge = numHuge = numGPU = 0;
	std::vector<Job*> jobVector = simulation->getVecJobs();
	for (int i = 0; i < jobVector.size(); ++i)
	{
		if (jobVector[i]->isShortJob()) {
			numShort++;
		}
		else if (jobVector[i]->isMediumJob()) {
			numMedium++;
		}
		else if (jobVector[i]->isLargeJob()) {
			numLarge++;
		}
		else if (jobVector[i]->isHugeJob()) {
			numHuge++;
		}
		else if (jobVector[i]->isGPUJob()) {
			numGPU++;
		}
	}
	std::vector<int> res = { numShort, numMedium, numLarge, numHuge, numGPU };
	return res;
}

double computeNumberOfNodeHoursConsumed(Simulation* simulation) {
	double totalNumberOfNodeHoursConsumed = 0.0;
	std::vector<Job*> jobVector = simulation->getVecJobs();
	for (int i = 0; i < jobVector.size(); ++i) {
		double nodes = (double)jobVector[i]->getNodesRequired();
		double hours = (double)jobVector[i]->getJobDuration() / 3600;
		totalNumberOfNodeHoursConsumed += nodes * hours;
	}
	return totalNumberOfNodeHoursConsumed;
}

double computeUtilizationRatio(Simulation* simulation, double numberOfNodesInput) {
	Data data;
	double numberOfNodes = 0;
	std::vector<NodeCount> nodeCountVector = simulation->getVecNodeCounts();
	if (numberOfNodesInput != 0) {
		numberOfNodes = numberOfNodesInput;
	}
	else {
		numberOfNodes = data.MIN_NUMBER_OF_NODES;
	}
	double nodeHoursConsumed = computeNumberOfNodeHoursConsumed(simulation);
	double nodeHoursAvailable = (nodeCountVector[nodeCountVector.size() - 1].getTime() / 3600) * numberOfNodes;
	return nodeHoursConsumed / nodeHoursAvailable;
}



double computeTotalPricePaidByUsers(Simulation* simulation) {
	int totalPrice = 0;
	std::vector<Job*> jobVector = simulation->getVecJobs();
	for (int i = 0; i < jobVector.size(); ++i) {
		totalPrice += jobVector[i]->computePrice();
	}
	return totalPrice;
}

std::vector<long double> computeAvgWaitTimeInEachQueue(Simulation* simulation) {
	long double waitShort, waitMedium, waitLarge, waitHuge, waitGPU;
	waitShort = waitMedium = waitLarge = waitHuge = waitGPU = 0;

	long int sizeShort, sizeMedium, sizeLarge, sizeHuge, sizeGPU;
	sizeShort = sizeMedium = sizeLarge = sizeHuge = sizeGPU = 0;

	std::vector<Job*> jobVector = simulation->getVecJobs();
	for (int i = 0; i < jobVector.size(); ++i)
	{
		if (jobVector[i]->isShortJob()) {
			waitShort += (jobVector[i]->getStartTime() - jobVector[i]->getSubmissionTime())/3600;
			sizeShort++;
		}
		else if (jobVector[i]->isMediumJob()) {
			waitMedium += (jobVector[i]->getStartTime() - jobVector[i]->getSubmissionTime()) / 3600;
			sizeMedium++;
		}
		else if (jobVector[i]->isLargeJob()) {
			waitLarge += (jobVector[i]->getStartTime() - jobVector[i]->getSubmissionTime()) / 3600;
			sizeLarge++;
		}
		else if (jobVector[i]->isHugeJob()) {
			waitHuge += (jobVector[i]->getStartTime() - jobVector[i]->getSubmissionTime()) / 3600;
			sizeHuge++;
		}
		else if (jobVector[i]->isGPUJob()) {
			waitGPU += (jobVector[i]->getStartTime() - jobVector[i]->getSubmissionTime()) / 3600;
			sizeGPU++;
		}
	}
	long double avgShort = (long double)waitShort / (long double)sizeShort;
	long double avgMedium = (long double)waitMedium / (long double)sizeMedium;
	long double avgLarge = (long double)waitLarge / (long double)sizeLarge;
	long double avgHuge = (long double)waitHuge / (long double)sizeHuge;
	long double avgGPU = (long double)waitGPU / (long double)sizeGPU;

	std::vector<long double> res = { avgShort, avgMedium, avgLarge, avgHuge, avgGPU };
	return res;
}
double computeAvgTurnAroundTimeRatio(Simulation* simulation) {
	double total, count;
	total = count = 0.0;
	std::vector<Job*> jobVector = simulation->getVecJobs();
	for (int i = 0; i < jobVector.size(); ++i) {
		double a = (double)jobVector[i]->getEndTime() - (double)jobVector[i]->getSubmissionTime();
		double b = (double)jobVector[i]->getEndTime() - (double)jobVector[i]->getStartTime();
		total += a / b;
		count++;
	}
	return total / count;
}

double computeEconomicBalanceOfCentre(Simulation* simulation) {
	Data data;
	std::vector<NodeCount> nodeCountVector = simulation->getVecNodeCounts();
	double overallOperatingCost = (nodeCountVector[nodeCountVector.size() - 1].getTime() * data.OPERATING_COST);
	return computeTotalPricePaidByUsers(simulation) - overallOperatingCost;
}

void createOutputsDirectory() {
	std::string directory_name("outputs");
	std::filesystem::create_directory(directory_name);
}