#include "User.h"

// alternate constructor

User::User(int id, UserType type, double budget, int numMaxNodes) {
	this->id = id;
	this->type = type;
	this->budget = budget;
	this->numMaxNodes = numMaxNodes;
}

UserType User::getType() {
	return this->type;
}

int User::getId() {
	return this->id;
}

double User::getBudget() {
	return this->budget;
}

//method to check if enough credit for a specific job
bool User::checkBudget(Job * job) {
	 return this->budget > job->computePrice();
}


//method to decrease the budget of the user depending on the price of a given job
void User::decreaseBudget(Job * job) {
	this->budget -= job->computePrice();
}

//method to check if user's max number of nodes used at the same time won't be reached when adding a given job
bool User::checkNumMaxNodes(Job * job) {
	return this->numMaxNodes > job->getNodesRequired();
}
