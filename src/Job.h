#ifndef JOB_H // include guard
#define JOB_H

#include <iostream>
#include <string>
#include <ctime>
#include <algorithm>
#include "QueueType.h"
#include "Data.h"
class User;

/**
*
* The Job class that contains methods needed to
* \n create a new job and interact with it
*/
class Job : Data{
private:
    QueueType queueType;
    unsigned int submissionTime;
    User * user;
    bool GPUjob;
    unsigned int jobDuration;
    double price;
    int nodesRequired;
    int startTime;
    int endTime;
    int waitTime;
    double turnAroundTimeRatio;

public:
    // CONSTRUCTORS

    /**
    * Default constructor. Intialize a Job object
    * @param submissionTime Time the job was submitted at by the user
    * @param jobDuration Duration of the processing of the job by the supercomputer
    * @param nodesRequired Number of nodes required torun the job
    * @param isGPUJob Defines if the job required GPU nodes or not
    */
    Job(unsigned int submissionTime, unsigned int jobDuration, int nodesRequired, bool isGPUJob);

    // ACCESSOR METHODS
    
    /**
    * Compute the price of job depending on its duration
    * \n and the nodes it requires
    * @return double. Price of the job
    */
    double computePrice();

    /**
    * Check if job belongs to short queue
    * @see bool isMediumJob()
    * @see bool isLargeJob()
    * @see bool isHugeJob()
    * @see bool isGPUJob()
    * @return bool. True if short queue, false if not
    */
    bool isShortJob();

    /**
    * Check if job belongs to medium queue
    * @see bool isShortJob()
    * @see bool isLargeJob()
    * @see bool isHugeJob()
    * @see bool isGPUJob()
    * @return bool. True if medium queue, false if not
    */
    bool isMediumJob();

    /**
    * Check if job belongs to large queue
    * @see bool isShortJob()
    * @see bool isMediumJob()
    * @see bool isHugeJob()
    * @see bool isGPUJob()
    * @return bool. True if large queue, false if not
    */
    bool isLargeJob();

    /**
    * Check if job belongs to GPU queue
    * @see bool isShortJob()
    * @see bool isMediumJob()
    * @see bool isLargeJob()
    * @see bool isHugeJob()
    * @return bool. True if large queue, false if not
    */
    bool isGPUJob();

    /**
    * Check if job belongs to huge queue
    * @see bool isShortJob()
    * @see bool isMediumJob()
    * @see bool isLargeJob()
    * @see bool isGPUJob()
    * @return bool. True if huge queue, false if not
    */
    bool isHugeJob();

    /**
    * Normal public get method.
    * Get the time the job was submitted at
    * @return unsigned int. Time the job was submitted at
    */
    unsigned int getSubmissionTime();

    /**
    * Normal public get method.
    * Get the duration of the job
    * @return unsigned int. Duration of the job
    */
    unsigned int getJobDuration();

    /**
    * Normal public get method.
    * Get the number of nodes required to run the job
    * @return int. Number of nodes required to run the job
    */
    int getNodesRequired();

    /**
    * Normal public get method.
    * Get the start time of job in seconds
    * @return unsigned int. Start time of the job
    */
    unsigned int getStartTime();

    /**
    * Normal public get method.
    * Get the end time of job in seconds
    * @return unsigned int. End time of the job
    */
    unsigned int getEndTime();

    /**
    * Normal public get method.
    * Get the user that sent the job request
    * @return User*. Pointer to user that sent the job request
    */
    User * getUser();

    /**
    * Normal public set method.
    * Set the user that sent the job request
    * @param user User to assign the job to
    */
    void setUser(User * user);

    /**
    * Normal public set method.
    * Set the start time of job
    * @param startTime Start time to assign to job
    */
    void setStartTime(unsigned int startTime);

    /**
    * Normal public set method.
    * Set the end time of job
    * @param startTime End time to assign to job
    */
    void setEndTime(unsigned int endTime);
};
#endif