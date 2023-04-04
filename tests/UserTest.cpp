#include "pch.h"
#include "CppUnitTest.h"
#include "../src/Data.h"
#include "../src/User.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UserTest
{
	TEST_CLASS(UserTest)
	{
	public:
		Data data;
		int id = 100;
		UserType type = UserType::Student;
		double budget = 1000;
		int numMaxNodes = 128;
		User* dummyUser = new User(id, type, budget, numMaxNodes);

		// Unit Tests
		TEST_METHOD(getType)
		{
			// Test getType() method
			if (dummyUser->getType() == UserType::Student) {
				Assert::AreEqual(1, 1);
			}
			else {
				Assert::AreEqual(1, 0);
			}
		}

		TEST_METHOD(getId)
		{
			// Test getId() method
			Assert::AreEqual(dummyUser->getId(), id);
		}

		TEST_METHOD(getBudget)
		{
			// Test getBudget() method
			Assert::AreEqual(dummyUser->getBudget(), 1000.0);
		}

		// Integration Tests
		unsigned int submissionTime = 135435;
		unsigned int jobDuration = 111752;
		int nodesRequired = 4;
		bool isGPUJob = false;
		Job* dummyJob = new Job(submissionTime, jobDuration, nodesRequired, isGPUJob);

		TEST_METHOD(checkBudget)
		{
			// Test checkBudget() method
			bool res = dummyUser->checkBudget(dummyJob);
			Assert::AreEqual(res, true);
		}
		TEST_METHOD(decreaseBudget)
		{
			// Test decreaseBudget() method
			dummyUser->decreaseBudget(dummyJob);
			Assert::AreEqual(dummyUser->getBudget(), 987,5831);
		}

		TEST_METHOD(checkNumMaxNodes)
		{
			// Test checkNumMaxNodes() method
			bool res = dummyUser->checkNumMaxNodes(dummyJob);
			Assert::AreEqual(res, true);
		}
	};
}
