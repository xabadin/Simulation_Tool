#ifndef USER_H // include guard
#define USER_H

#include "Job.h"
#include "Data.h"
#include "UserType.h"

/**
*
* The User class that contains methods needed
* \n to create a new user and interact with it
*/

class User : Data {
private:
    int id;
    UserType type;
    double budget;
    int numMaxNodes;

public:

    // CONSTRUCTORS

    /**
    * Alternate constructor. Build a User object 
    * @param id User's id
    * @param type User type (IT, Researcher, Student)
    * @param budget User's budget spent to send job requests
    * @param numMaxNodes Number maximum of nodes the user's jobs can use at the same time
    */
    User(int id, UserType type, double budget, int numMaxNodes);

    // ACCESSOR METHODS

    /**
    * Normal public get method.
    * Get the type of the user
    * @return UserType. Type of the user
    */
    UserType getType();
    
    /**
    * Normal public get method.
    * Get the id of the user
    * @return int. Id of the user
    */
    int getId();

    /**
    * Normal public get method.
    * Get the budget of the user
    * @return double. Budget of the user
    */
    double getBudget();

    /**
    * Check if the user has enough credit for a given job
    * @ param job Pointer to job to test
    * @return bool. True if user as enough credit, false either
    */
    bool checkBudget(Job * job);

    /**
    * Update the budget of the user depending on the price of a given job
    * @ param job Pointer to job which price will decrease the budget
    */
    void decreaseBudget(Job * job);

    /**
    * Check if the user's max number of nodes isn't reached
    * and has enough for a given job
    * @ param job Pointer to job to test
    */
    bool checkNumMaxNodes(Job * job);
};

#endif

