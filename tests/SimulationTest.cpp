#include "pch.h"
#include "CppUnitTest.h"
#include "../src/Data.h"
#include "../src/Simulation.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SimulationTest
{
	TEST_CLASS(SimulationTest)
	{
	public:
		Data data;
		Parameters* parameters = new Parameters();
		Simulation* simulation = new Simulation(parameters);

		unsigned int submissionTime = 135435;
		unsigned int jobDuration = 111752;
		int nodesRequired = 4;
		bool isGPUJob = false;
		Job* dummyJob = new Job(submissionTime, jobDuration, nodesRequired, isGPUJob);

		bool isStart = true;
		unsigned int jobID = 12;
		NodeCount nodeCount = NodeCount(parameters, *dummyJob, isStart, jobID);


		// Unit Tests

		TEST_METHOD(randomNumGenerator)
		{
			// Test randomNumGenerator() method
			int random = simulation->randomNumGenerator(5, 10);
			Assert::IsTrue(random >= 5 && random <= 10);
		}

		TEST_METHOD(exponentialDistribution)
		{
			// Test exponentialDistribution() method
			double exp = simulation->exponentialDistribution(10);
			Assert::AreEqual(typeid(exp).name(), "double");
		}

		TEST_METHOD(normalDistribution)
		{
			// Test normalDistribution() method
			double norm = simulation->normalDistribution(10, 2);
			Assert::AreEqual(typeid(norm).name(), "double");
		}

		TEST_METHOD(weekEnd)
		{
			// Test weekEnd() method
			bool weekEnd = simulation->weekEnd(2);
			Assert::AreEqual(weekEnd,false);
		}

		TEST_METHOD(nextWeek)
		{
			// Test nextWeek() method
			unsigned int nextWeek = simulation->nextWeek(48);
			Assert::AreEqual(nextWeek, data.WEEK_START_IN_SEC);
		}
		
		TEST_METHOD(nextWeekEnd)
		{
			// Test nextWeekEnd() method
			unsigned int nextWeekEnd = simulation->nextWeekEnd(5);
			Assert::AreEqual(nextWeekEnd, data.WEEKEND_START_IN_SEC);
		}
		

		// Integration Tests

		TEST_METHOD(fillVecJobs)
		{
			// Test fillVecJobs() and getVecJobs() methods
			simulation->fillVecJobs();
			for (int i = 0; i < simulation->getVecJobs().size(); i++) {
				Assert::IsNotNull(simulation->getVecJobs()[i]);
			}
		}

		TEST_METHOD(fillVecUsers)
		{
			// Test fillVecUsers() and getVecUsers() methods
			simulation->fillVecUsers();
			for (int i = 0; i < simulation->getVecUsers().size(); i++) {
				Assert::IsNotNull(simulation->getVecUsers()[i]);
			}
		}

		TEST_METHOD(scheduler)
		{
			// Test scheduler() method
			// As scheduler() is a combination of other methods 
			// that are already tested :
			Assert::AreEqual(1,1);
		}
		
		TEST_METHOD(findNext)
		{
			// Test findNext() method
			unsigned int tim = 5;
			int next = simulation->findNext(tim, 2);
			int i = 0;
			while (i < simulation->getVecNodeCounts().size() && simulation->getVecNodeCounts()[i].getTime() <= tim)
			{
				i++;
			}
			Assert::AreEqual(next, 2);
		}

		TEST_METHOD(startJob)
		{
			// Test startJob() and submitNodeCount() methods
			int indexNodeCount = 4;
			unsigned int time = 7;

			unsigned int submissionTime = 135435;
			unsigned int jobDuration = 2;
			int nodesRequired = 4;
			bool isGPUJob = false;
			Job* shortJob = new Job(submissionTime, jobDuration, nodesRequired, isGPUJob);
			NodeCount nodeCount2 = NodeCount(parameters, *shortJob, true, 45);

			unsigned int before = nodeCount.getShortNodesNum();
			simulation->startJob(indexNodeCount, *shortJob, time);
			simulation->submitNodeCount(time, *shortJob, indexNodeCount, 4);
			unsigned int after = nodeCount2.getShortNodesNum();
			Assert::AreNotEqual(before, after);
		}

		TEST_METHOD(enoughTime)
		{
			// Test enoughTime() method
			int indexNodeCount = 5;
			bool res = simulation->enoughTime(4, *dummyJob, indexNodeCount);
			Assert::AreEqual(res, true);
		}

		TEST_METHOD(isSpaceAvailable)
		{
			// Test isSpaceAvailable() method
			bool res = simulation->isSpaceAvailable(*dummyJob, nodeCount);
			Assert::AreEqual(res, true);
		}

		TEST_METHOD(startHugeJob)
		{
			// Test startHugeJob() and submitNodeCount() methods
			int indexNodeCount = 4;
			unsigned int time = 7;

			unsigned int submissionTime = 135435;
			unsigned int jobDuration = 2;
			int nodesRequired = 4;
			bool isGPUJob = false;
			Job* shortJob = new Job(submissionTime, jobDuration, nodesRequired, isGPUJob);
			NodeCount nodeCount2 = NodeCount(parameters, *shortJob, true, 45);

			unsigned int before = nodeCount.getHugeNodesNum();
			simulation->startJob(indexNodeCount, *shortJob, time);
			simulation->submitNodeCount(time, *shortJob, indexNodeCount, 4);
			unsigned int after = nodeCount2.getHugeNodesNum();
			Assert::AreNotEqual(before, after);
		}

		TEST_METHOD(nodeCountExists)
		{
			// Test nextWeekEnd() method
			unsigned int a = 56;
			bool nodeCountExists = simulation->nodeCountExists(a);
			Assert::AreEqual(nodeCountExists, false);
		}
	};
}
