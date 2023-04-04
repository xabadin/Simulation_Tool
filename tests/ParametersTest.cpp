#include "pch.h"
#include "CppUnitTest.h"
#include "../src/Data.h"
#include "../src/Parameters.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ParametersTest
{
	TEST_CLASS(ParametersTest)
	{
	public:
		Data data;
		Parameters* parameters = new Parameters();

		// Unit Tests
		TEST_METHOD(getNumberOfUsers)
		{
			// Test getNumberOfUsers() and setNumberOfUsers() methods
			parameters->setNumberOfUsers(500);
			const int users = parameters->getNumberOfUsers();
			Assert::AreEqual(users, 500);
		}

		TEST_METHOD(getNumberOfJobs)
		{
			// Test getNumberOfJobs() and setNumberOfJobs() methods
			parameters->setNumberOfJobs(3);
			const int jobs = parameters->getNumberOfJobs();
			Assert::AreEqual(jobs, 3);
		}

		TEST_METHOD(getNumberOfNodes)
		{
			// Test getNumberOfNodes() and setNumberOfNodes() methods
			parameters->setNumberOfNodes(157);
			const int nodes = parameters->getNumberOfNodes();
			Assert::AreEqual(nodes, 157);
		}

		TEST_METHOD(getNumberOfShortNodes)
		{
			// Test getNumberOfShortNodes() method
			const int shortNodes = parameters->getNumberOfShortNodes();
			Assert::AreEqual(shortNodes, (data.MIN_NUMBER_OF_NODES - data.NUMBER_OF_GPU_NODES) / 10);
		}

		TEST_METHOD(getNumberOfMediumNodes)
		{
			// Test getNumberOfMediumNodes() method
			const int mediumNodes = parameters->getNumberOfMediumNodes();
			Assert::AreEqual(mediumNodes, (data.MIN_NUMBER_OF_NODES - data.NUMBER_OF_GPU_NODES) / 3);
		}

		TEST_METHOD(getNumberOfLargeNodes)
		{
			// Test getNumberOfLargeNodes() method
			const int largeNodes = parameters->getNumberOfLargeNodes();
			Assert::AreEqual(largeNodes, (data.MIN_NUMBER_OF_NODES - data.NUMBER_OF_GPU_NODES) / 2);
		}

		TEST_METHOD(getNumberOfGPUNodes)
		{
			// Test getNumberOfLargeNodes() method
			const int gpuJobs = parameters->getNumberOfGPUNodes();
			Assert::AreEqual(gpuJobs, data.NUMBER_OF_GPU_NODES);
		}

		TEST_METHOD(getNumberOfHugeNodes)
		{
			// Test getNumberOfLargeNodes() method
			const int hugeJobs = parameters->getNumberOfHugeNodes();
			Assert::AreEqual(hugeJobs, data.MIN_NUMBER_OF_NODES - data.NUMBER_OF_GPU_NODES);
		}

		TEST_METHOD(getTraditionalNodeCost)
		{
			// Test getTraditionalNodeCost() and setTraditionalNodeCost() methods
			parameters->setTraditionalNodeCost(48);
			double tradCost = parameters->getTraditionalNodeCost();
			Assert::AreEqual(tradCost, 48.0);
		}

		TEST_METHOD(getAcceleratedNodeCost)
		{
			// Test getAcceleratedNodeCost() and setAcceleratedNodeCost() methods
			parameters->setAcceleratedNodeCost(27);
			double accelCost = parameters->getAcceleratedNodeCost();
			Assert::AreEqual(accelCost, 27.0);
		}

		TEST_METHOD(getOperatingCost)
		{
			// Test getOperatingCost() and setOperatingCost() methods
			parameters->setOperatingCost(12);
			double accelCost = parameters->getOperatingCost();
			Assert::AreEqual(accelCost, 12.0);
		}

		TEST_METHOD(getStudentBudget)
		{
			// Test getOperatingCost() and setStudentBudget() methods
			parameters->setStudentBudget(22);
			const int studentBudget = parameters->getStudentBudget();
			Assert::AreEqual(studentBudget, 22);
		}

		TEST_METHOD(getStudentMaxNodes)
		{
			// Test getStudentMaxNodes() method
			const int studentMaxNodes = parameters->getStudentMaxNodes();
			Assert::AreEqual(studentMaxNodes, data.STUDENT_MAX_NODES);
		}

		TEST_METHOD(getResearcherBudget)
		{
			// Test getResearcherBudget() and setResearcherBudget() method
			parameters->setResearcherBudget(33);
			const int researcherBudget = parameters->getResearcherBudget();
			Assert::AreEqual(researcherBudget, 33);
		}

		TEST_METHOD(getResearcherMaxNodes)
		{
			// Test getResearcherMaxNodes() method
			const int researcherMaxNodes = parameters->getResearcherMaxNodes();
			Assert::AreEqual(researcherMaxNodes, data.RESEARCHER_MAX_NODES);
		}

	};
}
