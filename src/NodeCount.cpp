#include "NodeCount.h"

NodeCount::NodeCount(Parameters * parameters, Job job, bool isStart, unsigned int jobID)
{
	this->jobID = jobID;
	this->GPUNodesNum = parameters->getNumberOfGPUNodes();
	this->hugeNodesNum = parameters->getNumberOfHugeNodes();
	this->largeNodesNum = parameters->getNumberOfLargeNodes();
	this->mediumNodesNum = parameters->getNumberOfMediumNodes();
	this->shortNodesNum = parameters->getNumberOfShortNodes();
	this->isStart = isStart;
	if (isStart)
	{
		if (job.isGPUJob())
		{
			this->GPUNodesNum = parameters->getNumberOfGPUNodes() - job.getNodesRequired();
		}
		else if (job.isHugeJob())
		{
			this->hugeNodesNum = parameters->getNumberOfHugeNodes() - job.getNodesRequired();
		}
		else if (job.isLargeJob())
		{
			this->largeNodesNum = parameters->getNumberOfLargeNodes() - job.getNodesRequired();
		}
		else if (job.isMediumJob())
		{
			this->mediumNodesNum = parameters->getNumberOfMediumNodes() - job.getNodesRequired();
		}
		else if (job.isShortJob())
		{
			this->shortNodesNum = parameters->getNumberOfShortNodes() - job.getNodesRequired();
		}
		this->time = job.getStartTime();
	}
	else
	{
		if (job.isGPUJob())
		{
			this->GPUNodesNum = parameters->getNumberOfGPUNodes() + job.getNodesRequired();
		}
		else if (job.isHugeJob())
		{
			this->hugeNodesNum = parameters->getNumberOfHugeNodes() + job.getNodesRequired();
		}
		else if (job.isLargeJob())
		{
			this->largeNodesNum = parameters->getNumberOfLargeNodes() + job.getNodesRequired();
		}
		else if (job.isMediumJob())
		{
			this->mediumNodesNum = parameters->getNumberOfMediumNodes() + job.getNodesRequired();
		}
		else if (job.isShortJob())
		{
			this->shortNodesNum = parameters->getNumberOfShortNodes() + job.getNodesRequired();
		}
		this->time = job.getEndTime();
	}
}

NodeCount::NodeCount(NodeCount& oldNodeCount, Job job, bool isStart, unsigned int jobID)
{
	this->jobID = jobID;
	this->GPUNodesNum = oldNodeCount.GPUNodesNum;
	this->hugeNodesNum = oldNodeCount.hugeNodesNum;
	this->largeNodesNum = oldNodeCount.largeNodesNum;
	this->mediumNodesNum = oldNodeCount.mediumNodesNum;
	this->shortNodesNum = oldNodeCount.shortNodesNum;
	this->isStart = isStart;
	if (isStart)
	{
		if (job.isGPUJob())
		{
			this->GPUNodesNum = oldNodeCount.GPUNodesNum - job.getNodesRequired();
		}
		else if (job.isHugeJob())
		{
			this->hugeNodesNum = oldNodeCount.hugeNodesNum - job.getNodesRequired();
		}
		else if (job.isLargeJob())
		{
			this->largeNodesNum = oldNodeCount.largeNodesNum - job.getNodesRequired();
		}
		else if (job.isMediumJob())
		{
			this->mediumNodesNum = oldNodeCount.mediumNodesNum - job.getNodesRequired();
		}
		else if (job.isShortJob())
		{
			this->shortNodesNum = oldNodeCount.shortNodesNum - job.getNodesRequired();
		}
		this->time = job.getStartTime();
	}
	else 
	{
		if (job.isGPUJob())
		{
			this->GPUNodesNum = oldNodeCount.GPUNodesNum + job.getNodesRequired();
		}
		else if (job.isHugeJob())
		{
			this->hugeNodesNum = oldNodeCount.hugeNodesNum + job.getNodesRequired();
		}
		else if (job.isLargeJob())
		{
			this->largeNodesNum = oldNodeCount.largeNodesNum + job.getNodesRequired();
		}
		else if (job.isMediumJob())
		{
			this->mediumNodesNum = oldNodeCount.mediumNodesNum + job.getNodesRequired();
		}
		else if (job.isShortJob())
		{
			this->shortNodesNum = oldNodeCount.shortNodesNum + job.getNodesRequired();
		}
		this->time = job.getEndTime();
	}
}

unsigned int NodeCount::getTime()
{
	return this->time;
}

void NodeCount::refreshNodeCount(Job job) 
{
	if (job.isGPUJob())
	{
		this->GPUNodesNum -= job.getNodesRequired();
	}
	else if (job.isHugeJob())
	{
		this->hugeNodesNum = job.getNodesRequired();
	}
	else if(job.isLargeJob())
	{
		this->largeNodesNum -= job.getNodesRequired();
	}
	else if (job.isMediumJob())
	{
		this->mediumNodesNum -= job.getNodesRequired();
	}
	else if (job.isShortJob())
	{
		this->shortNodesNum -= job.getNodesRequired();
	}
}

unsigned int NodeCount::getHugeNodesNum()
{
	return this->hugeNodesNum;
}

unsigned int NodeCount::getGPUNodesNum()
{
	return this->GPUNodesNum;
}

unsigned int NodeCount::getLargeNodesNum()
{
	return this->largeNodesNum;
}

unsigned int NodeCount::getMediumNodesNum()
{
	return this->mediumNodesNum;
}

unsigned int NodeCount::getShortNodesNum()
{
	return this->shortNodesNum;
}

bool NodeCount::getIsStart()
{
	return this->isStart;
}

unsigned int NodeCount::getJobID()
{
	return this->jobID;
}