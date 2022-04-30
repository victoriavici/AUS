#include "vector_test.h"
#include "../../structures/vector/vector.h"

namespace tests
{
// VectorTestInterface:

    VectorTestInterface::VectorTestInterface() :
        SimpleTest("Interface")
    {
    }

    void VectorTestInterface::test()
    {
        structures::Vector* vector = new structures::Vector(10);
        vector->size();
        vector->assign(*vector);
        vector->equals(*vector);
        vector->at(0);
        vector->getBytePointer(0);
       // structures::Vector::copy(*vector, 0, *vector, 0, 1);
        delete vector;
        SimpleTest::logPass("Compiled.");
    }



// VectorTestOverall:

    VectorTestOverall::VectorTestOverall() :
        ComplexTest("Vector")
    {
        addTest(new VectorTestInterface());
        addTest(new VectortestAt());
        addTest(new VectortestCopyConstructor());
    }
    VectortestAt::VectortestAt() :
       
        SimpleTest("Vector test at")
    {
    }
    void VectortestAt::test()
    {
        structures::Logger::getInstance().logInfo("Zacal test vektor at");
        SimpleTest::startStopwatch();

        structures::Vector* testVector = new structures::Vector(10);
        SimpleTest::assertTrue(testVector->size() == 10, "testujem vektorsize");
        for (int i = 0; i < 10; i++) {
            testVector->at(i) = i;
        }
        for (int i = 0; i < 10; i++) {
            SimpleTest::assertTrue(testVector->at(i) == i, "testujem vector::at(" +std::to_string(i) + ")");
            SimpleTest::assertTrue(*(testVector->getBytePointer(i)) == i, "testujem vector::getbytepointer(" + std::to_string(i) + ")");
        }

        delete testVector;

        SimpleTest::stopStopwatch();
        structures::Logger::getInstance().logDuration(0, SimpleTest::getElapsedTime(), "a trval tolkoto");
        //SimpleTest::logInfo("Funguje");

    }
    VectortestCopyConstructor::VectortestCopyConstructor() :
        SimpleTest("Vector test copy construsctor")
    {
    }
    void VectortestCopyConstructor::test()
    {
        structures::Vector* testVector = new structures::Vector(10);
        for (int i = 0; i < 10; i++) {
            testVector->at(i) = i;
        }
        structures::Vector* copyVector = new structures::Vector(*testVector);
        SimpleTest::assertTrue(copyVector->equals(*testVector), "Rovnake po vytvoreni");
        copyVector->at(1) = 10;
        SimpleTest::assertFalse(copyVector->equals(*testVector), "Rozdielne po zmene 1. bytu");
        testVector->assign(*copyVector);
        SimpleTest::assertTrue(copyVector->equals(*testVector), "Rovnake nakonci");

        delete testVector;
        delete copyVector;
    }
}