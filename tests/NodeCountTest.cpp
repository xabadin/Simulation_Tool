#include "pch.h"
#include "CppUnitTest.h"
#include "../src/Data.h"
#include "../src/NodeCount.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace NodeCountTest
{
	TEST_CLASS(NodeCountTest)
	{
	public:
		Data data;
		Parameters* parameters = new Parameters();
		unsigned int submissionTime = 135435;
		unsigned int jobDuration = 111752;
		int nodesRequired = 4;
		bool isGPUJob = false;
		Job* dummyJob = new Job(submissionTime, jobDuration, nodesRequired, isGPUJob);
		bool isStart = true;
		unsigned int jobID = 12;
		NodeCount nodeCount = NodeCount(parameters, *dummyJob, isStart, jobID);

		// Integration Tests
		TEST_METHOD(getHugeNodesNum)
		{
			// Test getHugeNodesNum() method
			unsigned int hugeNodeNum = nodeCount.getHugeNodesNum();
			Assert::AreEqual(hugeNodeNum, parameters->getNumberOfHugeNodes() - dummyJob->getNodesRequired());
		}

		TEST_METHOD(getLargeNodesNum)
		{
			// Test getLargeNodesNum() method
			unsigned int largeNodeNum = nodeCount.getLargeNodesNum();
			Assert::AreEqual(largeNodeNum, parameters->getNumberOfLargeNodes());
		}

		TEST_METHOD(getMediumNodesNum)
		{
			// Test getMediumNodesNum() method
			unsigned int mediumNodeNum = nodeCount.getMediumNodesNum();
			Assert::AreEqual(mediumNodeNum, parameters->getNumberOfMediumNodes());
		}

		TEST_METHOD(getShortNodesNum)
		{
			// Test getShortNodesNum() method
			unsigned int shortNodeNum = nodeCount.getShortNodesNum();
			Assert::AreEqual(shortNodeNum, parameters->getNumberOfShortNodes());

		}

		TEST_METHOD(getGPUNodesNum)
		{
			// Test getGPUNodesNum() method
			unsigned int gpuNodeNum = nodeCount.getGPUNodesNum();
			Assert::AreEqual(gpuNodeNum, parameters->getNumberOfGPUNodes());
		}

		TEST_METHOD(getTime)
		{
			// Test getTime() method
			unsigned int time = nodeCount.getTime();
			Assert::AreEqual(time, dummyJob->getStartTime());
		}

		TEST_METHOD(getJobID)
		{
			// Test getJobID() method
			int jobId = nodeCount.getJobID();
			Assert::AreEqual(jobId, 12);
		}

		TEST_METHOD(refreshNodeCount)
		{
			// Test refreshNodeCount() method
			unsigned int before = nodeCount.getHugeNodesNum();
			nodeCount.refreshNodeCount(*dummyJob);
			unsigned int after = nodeCount.getHugeNodesNum();
			Assert::AreNotEqual(before, after);
		}

		TEST_METHOD(getIsStart)
		{
			// Test getIsStart() method
			bool isStart = nodeCount.getIsStart();
			Assert::AreEqual(isStart, true);
		}
	};
}
