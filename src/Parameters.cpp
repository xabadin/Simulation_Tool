#include "Parameters.h"

//Default contructor - The default input values are defined in the "Data.h" header file.

Parameters::Parameters() {
	this->numberOfUsers = NUMBER_OF_USERS;

	this->numberOfJobs = NUMBER_OF_JOBS;

	this->numberOfNodes = MIN_NUMBER_OF_NODES;

	//10% of the nodes need to be reserved for the short queue
	this->numberOfShortNodes = (numberOfNodes - NUMBER_OF_GPU_NODES) / 10;

	//30% of the nodes need to be reserved for the medium queue
	this->numberOfMediumNodes = (numberOfNodes - NUMBER_OF_GPU_NODES) / 3;

	//50% of the nodes need to be reserved for the short queue
	this->numberOfLargeNodes = (numberOfNodes - NUMBER_OF_GPU_NODES) / 2;

	//8 GPU nodes
	this->numberOfGPUNodes = NUMBER_OF_GPU_NODES;

	//All the nodes need to be reserved for the short queue except the GPU nodes
	this->numberOfHugeNodes = numberOfNodes - NUMBER_OF_GPU_NODES;

	this->traditionalNodeCost = TRADITIONAL_NODE_COST;
	this->acceleratedNodeCost = ACCELERATED_NODE_COST;

	this->operatingCost = OPERATING_COST;

	this->studentBudget = STUDENT_BUDGET;

	this->studentMaxNodes = STUDENT_MAX_NODES;

	this->researcherBudget = RESEARCHER_BUDGET;

	this->researcherMaxNodes = RESEARCHER_MAX_NODES;
}

Parameters::Parameters(unsigned int numberOfUsers, unsigned int numberOfJobs, unsigned int numberOfNodes, double traditionalNodeCost,
	double acceleratedNodeCost, double studentBudget, unsigned int studentMaxNodes, double researcherBudget, unsigned int researcherMaxNodes) {

	if (numberOfUsers != 0) {
		this->numberOfUsers = numberOfUsers;
	}
	else {
		this->numberOfUsers = NUMBER_OF_USERS;
	}

	if (numberOfJobs != 0) {
		this->numberOfJobs = numberOfJobs;
	}
	else {
		this->numberOfJobs = NUMBER_OF_JOBS;
	}

	if (numberOfNodes != 0) {
		this->numberOfNodes = numberOfNodes;
	}
	else {
		this->numberOfNodes = MIN_NUMBER_OF_NODES;
	}

	if (traditionalNodeCost != 0) {
		this->traditionalNodeCost = traditionalNodeCost / 3600;
	}
	else {
		this->traditionalNodeCost = TRADITIONAL_NODE_COST;
	}

	if (acceleratedNodeCost != 0) {
		this->acceleratedNodeCost = acceleratedNodeCost / 3600;
	}
	else {
		this->acceleratedNodeCost = ACCELERATED_NODE_COST;
	}

	if (studentBudget != 0) {
		this->studentBudget = studentBudget;
	}
	else {
		this->studentBudget = STUDENT_BUDGET;
	}

	if (studentMaxNodes != 0) {
		this->studentMaxNodes = studentMaxNodes;
	}
	else {
		this->studentMaxNodes = STUDENT_MAX_NODES;
	}

	if (researcherBudget != 0) {
		this->researcherBudget = researcherBudget;
	}
	else {
		this->researcherBudget = RESEARCHER_BUDGET;
	}

	if (researcherMaxNodes != 0) {
		this->researcherMaxNodes = researcherMaxNodes;
	}
	else {
		this->researcherMaxNodes = RESEARCHER_MAX_NODES;
	}

	//10% of the nodes need to be reserved for the short queue
	this->numberOfShortNodes = (this->numberOfNodes - NUMBER_OF_GPU_NODES) / 10;

	//30% of the nodes need to be reserved for the medium queue
	this->numberOfMediumNodes = (this->numberOfNodes - NUMBER_OF_GPU_NODES) / 3;

	//50% of the nodes need to be reserved for the short queue
	this->numberOfLargeNodes = (this->numberOfNodes - NUMBER_OF_GPU_NODES) / 2;

	//8 GPU nodes
	this->numberOfGPUNodes = NUMBER_OF_GPU_NODES;

	//All the nodes need to be reserved for the short queue except the GPU nodes
	this->numberOfHugeNodes = this->numberOfNodes - NUMBER_OF_GPU_NODES;

	this->operatingCost = OPERATING_COST;
}

//GETTERS
// return number of users
unsigned int Parameters::getNumberOfUsers() {
	return this->numberOfUsers;
}

// Returns the number of jobs when this value is not generated randomly
unsigned int Parameters::getNumberOfJobs() {
	return this->numberOfJobs;
}

// Returns the total number of system nodes
unsigned int Parameters::getNumberOfNodes() {
	return this->numberOfNodes;
}

unsigned int Parameters::getNumberOfShortNodes() {
	return this->numberOfShortNodes;
}

unsigned int Parameters::getNumberOfMediumNodes() {
	return this->numberOfMediumNodes;
}

unsigned int Parameters::getNumberOfLargeNodes() {
	return this->numberOfLargeNodes;
}

unsigned int Parameters::getNumberOfGPUNodes() {
	return this->numberOfGPUNodes;
}

unsigned int Parameters::getNumberOfHugeNodes() {
	return this->numberOfHugeNodes;
}

// Returns the usage price of the system per node second
double Parameters::getTraditionalNodeCost() {
	return this->traditionalNodeCost;
}

// Returns the usage price of the system per node second
double Parameters::getAcceleratedNodeCost() {
	return this->acceleratedNodeCost;
}

// Returns the operational cost of the system per second
double Parameters::getOperatingCost() {
	return this->operatingCost;
}

// Returns the student budget
double Parameters::getStudentBudget() {
	return this->studentBudget;
}

// Returns the maximum of nodes that a student can request simultaneously
unsigned int Parameters::getStudentMaxNodes() {
	return this->studentMaxNodes;
}

// Returns the researcher budget 
double Parameters::getResearcherBudget() {
	return this->researcherBudget;
}

// Returns the maximum of nodes that a researcher can request simultaneously
unsigned int Parameters::getResearcherMaxNodes() {
	return this->researcherMaxNodes;
}

//SETTERS
// Defines the number of users
void Parameters::setNumberOfUsers(unsigned int numberOfUsers) {
	this->numberOfUsers = numberOfUsers;
}

// Defines the number of jobs of a new simulation
void Parameters::setNumberOfJobs(unsigned int numberOfJobs) {
	this->numberOfJobs = numberOfJobs;
}

// Defines the total number of system nodes
void Parameters::setNumberOfNodes(unsigned int numberOfNodes) {
	this->numberOfNodes = numberOfNodes;
}

// Defines the usage price of the system's traditional nodes per second
void Parameters::setTraditionalNodeCost(double traditionalNodeCost) {
	this->traditionalNodeCost = traditionalNodeCost;
}

// Defines the usage price of the system's accelerated nodes per second
void Parameters::setAcceleratedNodeCost(double acceleratedNodeCost) {
	this->acceleratedNodeCost = acceleratedNodeCost;
}

// Defines the operational cost of the system per core second
void Parameters::setOperatingCost(double operatingCost) {
	this->operatingCost = operatingCost;
}

// Defines the student budget 
void Parameters::setStudentBudget(double budget) {
	this->studentBudget = budget;
}

// Defines the researcher budget 
void Parameters::setResearcherBudget(double budget) {
	this->researcherBudget = budget;
}
