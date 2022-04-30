#include "array_test.h"
#include "../../structures/array/array.h"

namespace tests
{
// ArrayTestInterface:

	ArrayTestInterface::ArrayTestInterface() :
		SimpleTest("Interface")
	{
	}

	void ArrayTestInterface::test()
	{
		structures::Array<int>* testArray = new structures::Array<int>(10);
		testArray->copy(*testArray, 0, *testArray, 0, 1);
		testArray->isEmpty();
		testArray->assign(*testArray);
		testArray->equals(*testArray);
		testArray->at(0);
		testArray->size();
		delete testArray;
		SimpleTest::logPass("Compiled.");
	}

// ArrayTestOverall:

	ArrayTestOverall::ArrayTestOverall() :
		ComplexTest("Array")
	{
		addTest(new ArrayTestInterface);
		addTest(new ArrayTestAt);
		addTest(new ArrayTestCopyConstructor);
	}

	ArrayTestAt::ArrayTestAt() :
		SimpleTest("Array test At")
	{
	}
	void ArrayTestAt::test()
	{

		structures::Array<int>* testArray = new structures::Array<int>(10);
		SimpleTest::assertTrue(testArray->size() == 10, "testujem vektorsize");
		for (int i = 0; i < 10; i++) {
			testArray->at(i) = i;
		}
		for (int i = 0; i < 10; i++) {
			SimpleTest::assertTrue(testArray->at(i) == i, "testujem vector::at(" + std::to_string(i) + ")");
			//SimpleTest::assertTrue(*(testArray->get == i, "testujem vector::getbytepointer(" + std::to_string(i) + ")");
		}
		delete testArray;
	}
	ArrayTestCopyConstructor::ArrayTestCopyConstructor() :
		SimpleTest("Array test copyconstructor")
	{
	}
	void ArrayTestCopyConstructor::test()
	{
		structures::Array<int>* testArray = new structures::Array<int>(10);
		for (int i = 0; i < 10; i++) {
			testArray->at(i) = i;
		}
		structures::Array<int>* copyArray = new structures::Array<int>(*testArray);
		SimpleTest::assertTrue(copyArray->equals(*testArray), "Rovnake po vytvoreni");
		copyArray->at(1) = 10;
		SimpleTest::assertFalse(copyArray->equals(*testArray), "Rozdielne po zmene 1. bytu");
		testArray->assign(*copyArray);
		SimpleTest::assertTrue(copyArray->equals(*testArray), "Rovnake nakonci");

		delete testArray;
		delete copyArray;
	}
}

