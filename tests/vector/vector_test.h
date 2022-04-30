#pragma once

#include "../test.h"
//#include "logger.h"

namespace tests
{
    /// <summary>
    /// Zavola vsetky metody z rozhrania vektora avsak nekontroluje ich spravnost.
    /// Zabezpeci, ze vsetky metody budu prelozene kompilatorom.
    /// </summary>
    class VectorTestInterface
        : public SimpleTest
    {
    public:
        VectorTestInterface();
        void test() override;
    };

    class VectortestAt
        : public SimpleTest 
    {
    public:
        VectortestAt();
        void test() override;
    };

    class VectortestCopyConstructor
        : public SimpleTest
    {
    public:
        VectortestCopyConstructor();
        void test() override;
    };
    /// <summary>
    /// Zahrna v sebe vsetky testy, ktore testuju vektor.
    /// </summary>
    class VectorTestOverall
        : public ComplexTest
    {
    public:
        VectorTestOverall();
    };
}