#include "pch.h"
#include "CppUnitTest.h"
#include "../src/Data.h"
#include "../src/Job.cpp"
#include "../src/User.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace JobTest
{
	TEST_CLASS(JobTest)
	{
	public:
		Data data;
		unsigned int submissionTime = 135435;
		unsigned int jobDuration = 111752;
		int nodesRequired = 4;
		bool isGPUJob = false;
		Job* dummyJob = new Job(submissionTime, jobDuration, nodesRequired, isGPUJob);

		// Unit Tests
		TEST_METHOD(computePrice)
		{
			// Test computePrice() method
			Job* traditionalJob = new Job(submissionTime, jobDuration, nodesRequired, isGPUJob);
			Assert::AreEqual(traditionalJob->computePrice(), (double)(jobDuration) * (double)(nodesRequired)*data.TRADITIONAL_NODE_COST);
		}

		TEST_METHOD(isShortJob)
		{
			// Test isShortJob() method
			Job* shortJob = new Job(submissionTime, data.ONE_HOUR_IN_SEC, nodesRequired, isGPUJob);
			Assert::AreEqual(shortJob->isShortJob(), true);
		}

		TEST_METHOD(isMediumJob)
		{
			// Test isMediumJob() method
			Job* mediumJob = new Job(submissionTime, data.EIGHT_HOURS_IN_SEC, nodesRequired, isGPUJob);
			Assert::AreEqual(mediumJob->isMediumJob(), true);
		}

		TEST_METHOD(isLargeJob)
		{
			// Test isLargeJob() method
			Job* largeJob = new Job(submissionTime, data.SIXTEEN_HOURS_IN_SEC, nodesRequired, isGPUJob);
			Assert::AreEqual(largeJob->isLargeJob(), true);
		}

		TEST_METHOD(isHugeJob)
		{
			// Test isHugeJob() method
			Job* hugeJob = new Job(submissionTime, data.SIXTEEN_HOURS_IN_SEC + 1, nodesRequired, isGPUJob);
			Assert::AreEqual(hugeJob->isHugeJob(), true);
		}

		TEST_METHOD(isGpuJob)
		{
			// Test isGPUJob() method
			Job* GPUJob = new Job(submissionTime, jobDuration, nodesRequired, !isGPUJob);
			Assert::AreEqual(GPUJob->isGPUJob(), true);
		}

		TEST_METHOD(getSubmissionTime)
		{
			// Test getSubmissionTime() method
			Assert::AreEqual(dummyJob->getSubmissionTime(), submissionTime);
		}

		TEST_METHOD(getJobDuration)
		{
			// Test getJobDuration() method
			Assert::AreEqual(dummyJob->getJobDuration(), jobDuration);
		}

		TEST_METHOD(getNodesRequired)
		{
			// Test getNodesRequired() method
			Assert::AreEqual(dummyJob->getNodesRequired(), nodesRequired);
		}

		TEST_METHOD(getStartTime)
		{
			// Test getStartTime() and setStarTime() methods
			dummyJob->setStartTime(5);
			Assert::AreEqual(dummyJob->getStartTime(), (unsigned int)5);
		}

		TEST_METHOD(getEndTime)
		{
			// Test getEndTime() and setEndTime() methods
			dummyJob->setEndTime(10);
			Assert::AreEqual(dummyJob->getEndTime(), (unsigned int)10);
		}

		// Integration Tests

		TEST_METHOD(setUser)
		{
			// Test setUser() method
			User * user = new User(45, UserType::Student, 500.0, 128);
			dummyJob->setUser(user);
			Assert::AreEqual(dummyJob->getUser()->getId(), user->getId());
		}
	};
}
