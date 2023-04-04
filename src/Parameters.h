#ifndef Parameters_H // include guard
#define Parameters_H

#include "Data.h"

/**
*
*  The Parameters class that contains the input values of the simulation
*  \n as well as getters and setters to interact with them
*/
class Parameters : Data {
private:
    unsigned int numberOfNodes; // number of nodes initialized to min number of nodes

    //Number of nodes in each queue
    unsigned int numberOfShortNodes;
    unsigned int numberOfMediumNodes;
    unsigned int numberOfLargeNodes;
    unsigned int numberOfGPUNodes;
    unsigned int numberOfHugeNodes;

    double traditionalNodeCost; // price of a traditional node per second

    double acceleratedNodeCost; // price of an accelerated node per second

    double operatingCost; // Operational cost of the system per second

    double studentBudget; // Student budget

    unsigned int studentMaxNodes; // maximum of nodes that a student can request simultaneously

    double researcherBudget; // Researcher budget

    unsigned int researcherMaxNodes; // maximum of nodes that a researcher can request simultaneously

    unsigned int numberOfJobs; // Number of jobs

    unsigned int numberOfUsers; // Number of users

public:

    // CONSTRUCTORS

    /**
    * Default constructor. Intialize a Parameters object
    */
    Parameters();

    /**
    * Alternate constructor. Intialize a Parameters object
    * @param numberofUsers
    * @param numberOfJobs
    * @param numberOfNodes
    * @param traditionalNodeCost
    * @param acceleratedNodeCost
    * @param studentBudget
    * @param studentMaxNodes
    * @param researcherBudget
    * @param researcherMaxNodes
    */
    Parameters(unsigned int numberOfUsers, unsigned int numberOfJobs, unsigned int numberOfNodes, double traditionalNodeCost,
        double acceleratedNodeCost, double studentBudget, unsigned int studentMaxNodes, double researcherBudget, unsigned int researcherMaxNodes);


    // ACCESSOR METHODS

    // GETTERS

    /**
    * Normal public get method.
    * Get the number of users in simulation
    * @see void setNumberOfUsers(unsigned int numberOfUsers)
    * @return unsigned int. Number of users in simulation
    */
    unsigned int getNumberOfUsers();

    /**
    * Normal public get method.
    * Get the number of jobs in simulation
    * @see void setNumberOfJobs(unsigned int numberOfJobs)
    * @return unsigned int. Number of jobs in simulation
    */
    unsigned int getNumberOfJobs();

    /**
    * Normal public get method.
    * Get the number of system nodes used for the supercomputer in simulation
    * @see void setNumberOfNodes(unsigned int numberOfNodes)
    * @return unsigned int. Number of system nodes used for the supercomputer in simulation
    */
    unsigned int getNumberOfNodes();

    /**
    * Normal public get method.
    * Get the number of short nodes available in the system
    * @return unsigned int. Number of short nodes in the system
    */
    unsigned int getNumberOfShortNodes();

    /**
    * Normal public get method.
    * Get the number of medium nodes available in the system
    * @return unsigned int. Number of medium nodes in the system
    */
    unsigned int getNumberOfMediumNodes();

    /**
    * Normal public get method.
    * Get the number of large nodes available in the system
    * @return unsigned int. Number of large nodes in the system
    */
    unsigned int getNumberOfLargeNodes();

    /**
    * Normal public get method.
    * Get the number of GPU nodes available in the system
    * @return unsigned int. Number of GPU nodes in the system
    */
    unsigned int getNumberOfGPUNodes();

    /**
    * Normal public get method.
    * Get the number of huge nodes available in the system
    * @return unsigned int. Number of huge nodes in the system
    */
    unsigned int getNumberOfHugeNodes();

    /**
    * Normal public get method.
    * Get the usage price of traditional nodes of the system per second
    * @see void setTraditionalNodeCost(double traditionalNodeCost)
    * @return double. Usage price of traditional nodes of the system per second
    */
    double getTraditionalNodeCost();

    /**
    * Normal public get method.
    * Get the usage price of accelerated nodes of the system per second
    * @see void setAcceleratedNodeCost(double acceleratedNodeCost)
    * @return double. Usage price of accelerated nodes of the system per second
    */
    double getAcceleratedNodeCost();

    /**
    * Normal public get method.
    * Get the operational cost of the system per second
    * @see void setOperatingCost(double operatingCost)
    * @return double. Operational cost of the system per second
    */
    double getOperatingCost();

    /**
    * Normal public get method.
    * Get the budget allocated to students
    * @see void setStudentBudget(double budget)
    * @return double. Student budget
    */
    double getStudentBudget();

    /**
     * Normal public get method.
     * Get the maximum of nodes that a student can request simultaneously
     * @see void setStudentMaxNodes(double maxNodes)
     * @return unsgined int. Maximum of nodes that a student can request simultaneously
     */
    unsigned int getStudentMaxNodes();

    /**
    * Normal public get method.
    * Get the budget allocated to researchers
    * @see void setResearcherBudget(double budget)
    * @return double. Researcher budget
    */
    double getResearcherBudget();

    /**
    * Normal public get method.
    * Get the maximum of nodes that a researcher can request simultaneously
    * @see void setResearcherMaxNodes(double maxNodes)
    * @return unsigned int. Maximum of nodes that a researcher can request simultaneously
    */
    unsigned int getResearcherMaxNodes();

    // SETTERS

    /**
    * Normal public set method.
    * Set the number of users of a new simulation
    * @see unsigned int getNumberOfUsers()
    */
    void setNumberOfUsers(unsigned int numberOfUsers);

    /**
    * Normal public set method.
    * Set the number of jobs of a new simulation
    * @see unsigned int getNumberOfJobs()
    */
    void setNumberOfJobs(unsigned int numberOfJobs);

    /**
    * Normal public set method.
    * Set the number of system nodes used for the supercomputer in simulation
    * @see unsigned int getNumberOfNodes()
    */
    void setNumberOfNodes(unsigned int numberOfNodes);

    /**
    * Normal public set method.
    * Set the usage price of the system's traditional nodes per second
    * @see double getTraditionalNodeCost()
    */
    void setTraditionalNodeCost(double traditionalNodeCost);

    /**
    * Normal public set method.
    * Set the usage price of the system's traditional nodes per second
    * @see double getAcceleratedNodeCost()
    */
    void setAcceleratedNodeCost(double acceleratedNodeCost);

    /**
    * Normal public set method.
    * Set the operating cost of the system per core second
    * @see double getOperatingCost()
    */
    void setOperatingCost(double operatingCost);

    /**
    * Normal public set method.
    * Set the budget allocated to students
    * @see double getStudentBudget()
    */
    void setStudentBudget(double budget);

    /**
    * Normal public set method.
    * Set the budget allocated to researchers
    * @see double getResearcherBudget()
    */
    void setResearcherBudget(double budget);
};
#endif
