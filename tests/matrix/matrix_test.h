#pragma once
#include "../test.h"
#include "../../structures/matrix/matrix.h"
#include "../../structures/_logger/logger.h"

namespace tests
{
	/// <summary>
	/// Zavola vsetky metody z rozhrania matice avsak nekontroluje ich spravnost.
	/// Zabezpeci, ze vsetky metody budu prelozene kompilatorom.
	/// </summary>
	class MatrixTestInterface
		: public SimpleTest
	{
	public:
		MatrixTestInterface();
		void test() override;

	protected:
		virtual structures::Matrix<int>* makeMatrix(size_t rows, size_t cols) const = 0;
	};

	/// <summary>
	/// Zavola vsetky metody koherentnej matice.
	/// </summary>
	class CoherentMatrixTestInterface
		: public MatrixTestInterface
	{
	protected:
		structures::Matrix<int>* makeMatrix(size_t rows, size_t cols) const override;
	};

	/// <summary>
	/// Zavola vsetky metody nekoherentnej matice.
	/// </summary>
	class IncoherentMatrixTestInterface
		: public MatrixTestInterface
	{
	protected:
		structures::Matrix<int>* makeMatrix(size_t rows, size_t cols) const override;
	};

	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju CoherentMatrix.
	/// </summary>
	class CoherentMatrixTestOverall
		: public ComplexTest
	{
	public:
		CoherentMatrixTestOverall();
	};

	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju IncoherentMatrix.
	/// </summary>
	class IncoherentMatrixTestOverall
		: public ComplexTest
	{
	public:
		IncoherentMatrixTestOverall();
	};

	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju CoherrentMatrix a IncoherrentMatrix.
	/// </summary>
	class MatrixTestOverall
		: public ComplexTest
	{
	public:
		MatrixTestOverall();
	};

	class Matrix
		: public ComplexTest
	{
	public:
		Matrix();
	};


	class CoherentTestAt
		: public SimpleTest
	{
	public:
		CoherentTestAt();
		void test() override;
	};


	class CoherentTestCopyConstructor
		: public SimpleTest
	{
	public:
		CoherentTestCopyConstructor();
		void test() override;
	};


	class IncoherentTestAt
		: public SimpleTest
	{
	public:
		IncoherentTestAt();
		void test() override;
	};


	class IncoherentTestCopyConstructor
		: public SimpleTest
	{
	public:
		IncoherentTestCopyConstructor();
		void test() override;
	};

	class ScenarMatrix :
		public SimpleTest {
	public:
		ScenarMatrix(const char* nazov);
		void testScenar(int r, int c, double ppr, double ppc, double ppa);
	};
		
	class ScenarA :
		public ScenarMatrix {
	public:
		ScenarA();
		void test() override;
	};
	class ScenarB :
		public ScenarMatrix{
	public:
		ScenarB();
		void test() override;
	};
	class ScenarC :
		public ScenarMatrix {
	public:
		ScenarC();
		void test() override;
	};
	class ScenarD :
		public ScenarMatrix {
	public:
		ScenarD();
		void test() override;
	};

	class Zlozitosti :
		public SimpleTest {
	public:
		Zlozitosti();
		void test() override;
	};

	class ScenarE :
		public SimpleTest {
	public:
		ScenarE();
		void test() override;
	};
}