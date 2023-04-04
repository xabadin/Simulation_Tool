#include "Job.h"

// Alternate constructor
Job::Job(unsigned int submissionTime, unsigned int jobDuration, int nodesRequired, bool GPUjob) {
	this->submissionTime = submissionTime;
	this->nodesRequired = nodesRequired;
	this->GPUjob = GPUjob;
	if (GPUjob)
	{
		this->queueType = QueueType::GPUJob;
	}
	else if (jobDuration <= ONE_HOUR_IN_SEC) {
		this->queueType = QueueType::ShortJob;
	}
	else if (jobDuration > ONE_HOUR_IN_SEC && jobDuration <= EIGHT_HOURS_IN_SEC) {
		this->queueType = QueueType::MediumJob;
	}
	else if (jobDuration > EIGHT_HOURS_IN_SEC && jobDuration <= SIXTEEN_HOURS_IN_SEC) {
		this->queueType = QueueType::LargeJob;
	}
	else {
		this->queueType = QueueType::HugeJob;
	}
	this->jobDuration = jobDuration;
	this->endTime = 0;
	this->startTime = 0;
	this->turnAroundTimeRatio = 0;
	this->price = computePrice();
}

unsigned int Job::getSubmissionTime() {
	return this->submissionTime;
}

unsigned int Job::getJobDuration() {
	return this->jobDuration;
}

unsigned int Job::getStartTime() {
	return this->startTime;
}

unsigned int Job::getEndTime() {
	return this->endTime;
}

int Job::getNodesRequired() {
	return this->nodesRequired;
}

//If GPU the calcul is not the same (we need a price for traditional and accelerated nodes)
double Job::computePrice() {
	if (GPUjob) 
	{ 
		this->price = (double)(jobDuration) * (double)(nodesRequired)*ACCELERATED_NODE_COST;
	}
	else 
	{ 
		this->price = (double)(jobDuration) * (double)(nodesRequired)*TRADITIONAL_NODE_COST;	
	}
	return this->price;
}

bool Job::isShortJob() {
	return this->queueType == QueueType::ShortJob;
}

bool Job::isMediumJob() {
	return this->queueType == QueueType::MediumJob;
}

bool Job::isLargeJob() {
	return this->queueType == QueueType::LargeJob;
}

bool Job::isGPUJob() {
	return this->queueType == QueueType::GPUJob;
}

bool Job::isHugeJob() {
	return this->queueType == QueueType::HugeJob;
}

User * Job::getUser() {
	return this->user;
}

void Job::setUser(User * user)
{
	this->user = user;
}

void Job::setStartTime(unsigned int startTime)
{
	this->startTime = startTime;
}

void Job::setEndTime(unsigned int endTime)
{
	this->endTime = endTime;
}