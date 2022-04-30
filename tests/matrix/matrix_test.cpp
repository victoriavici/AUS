#include "matrix_test.h"
#include "../../structures/matrix/coherent_matrix.h"
#include "../../structures/matrix/incoherent_matrix.h"
#include <iostream>
#include <time.h>
#include "../../structures/heap_monitor.h"


namespace tests
{
	tests::MatrixTestInterface::MatrixTestInterface() :
		SimpleTest("Interface")
	{
	}

	void tests::MatrixTestInterface::test()
	{
		structures::Matrix<int>* matrix = this->makeMatrix(20, 20);
		matrix->assign(*matrix);
		matrix->equals(*matrix);
		matrix->size();
		matrix->isEmpty();
		matrix->getRowCount();
		matrix->getColumnCount();
		matrix->at(10, 10);
		delete matrix;
	}

	structures::Matrix<int>* CoherentMatrixTestInterface::makeMatrix(size_t rows, size_t cols) const
	{
		return new structures::CoherentMatrix<int>(rows, cols);
	}

	structures::Matrix<int>* IncoherentMatrixTestInterface::makeMatrix(size_t rows, size_t cols) const
	{
		return new structures::IncoherentMatrix<int>(rows, cols);
	}

	CoherentMatrixTestOverall::CoherentMatrixTestOverall() :
		ComplexTest("CoherentMatrix")
	{
		addTest(new CoherentMatrixTestInterface());
		addTest(new CoherentTestAt());
		addTest(new CoherentTestCopyConstructor());
		
	}

	IncoherentMatrixTestOverall::IncoherentMatrixTestOverall() :
		ComplexTest("IncoherentMatrix")
	{
		addTest(new IncoherentMatrixTestInterface());
		addTest(new IncoherentTestAt());
		addTest(new IncoherentTestCopyConstructor());
	}

	Matrix::Matrix() :
		ComplexTest("Matrix")
	{
		addTest(new ScenarA);
		addTest(new ScenarB);
		addTest(new ScenarC);
		addTest(new ScenarD);
		addTest(new Zlozitosti());
		addTest(new ScenarE());
	}
	

	MatrixTestOverall::MatrixTestOverall() :
		ComplexTest("Matrix")
	{
		addTest(new CoherentMatrixTestOverall());
		addTest(new IncoherentMatrixTestOverall());
		addTest(new Matrix());
	}
	CoherentTestAt::CoherentTestAt() :
		SimpleTest("Cohe test at")
	{	
	}

	void CoherentTestAt::test()
	{
		auto testCohe = new structures::CoherentMatrix<int>(5, 3);
		SimpleTest::assertTrue(testCohe->size() == 15, "testujem vektorsize");
		
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 3; j++)
			{
				testCohe->at(i, j) = i+j;
				
			}
		}
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 3; j++)
			{
				
				SimpleTest::assertTrue(testCohe->at(i, j) == i+j, "testujem vector::at(" + std::to_string(i) +", " + std::to_string(j) + ")");
				

			}
		}
		
		delete testCohe;
	}
	CoherentTestCopyConstructor::CoherentTestCopyConstructor()
		: SimpleTest("Coherent test copyconstructor")
	{
	}
	void CoherentTestCopyConstructor::test()
	{
		auto testCohe = new structures::CoherentMatrix<int>(5,3);
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 3; j++)
			{
				testCohe->at(i,j) = i+j;
			}
			
		}
		auto copyCohe = new structures::CoherentMatrix<int>(*testCohe);
		SimpleTest::assertTrue(copyCohe->equals(*testCohe), "Rovnake po vytvoreni");
		copyCohe->at(1,1) = 10;
		SimpleTest::assertFalse(copyCohe->equals(*testCohe), "Rozdielne po zmene 1. bytu");
		testCohe->assign(*copyCohe);
		SimpleTest::assertTrue(copyCohe->equals(*testCohe), "Rovnake nakonci");

		delete testCohe;
		delete copyCohe;
	}
	IncoherentTestAt::IncoherentTestAt()
		:SimpleTest("Incoherent Test At")
	{
	}
	void IncoherentTestAt::test()
	{
		auto testIncohe = new structures::IncoherentMatrix<int>(5, 3);
		SimpleTest::assertTrue(testIncohe->size() == 15, "testujem vektorsize");

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 3; j++)
			{
				testIncohe->at(i, j) = i + j;

			}
		}
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 3; j++)
			{

				SimpleTest::assertTrue(testIncohe->at(i, j) == i + j, "testujem vector::at(" + std::to_string(i) + ", " + std::to_string(j) + ")");


			}
		}

		delete testIncohe;
	}
	IncoherentTestCopyConstructor::IncoherentTestCopyConstructor()
		:SimpleTest("Incoherent Test CopyConstructor")
	{
	}
	void IncoherentTestCopyConstructor::test()
	{

		auto testIncohe = new structures::IncoherentMatrix<int>(5, 3);
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 3; j++)
			{
				testIncohe->at(i, j) = i + j;
			}

		}
		auto copyCohe = new structures::IncoherentMatrix<int>(*testIncohe);
		SimpleTest::assertTrue(copyCohe->equals(*testIncohe), "Rovnake po vytvoreni");
		copyCohe->at(0,0) = 10;
		SimpleTest::assertFalse(copyCohe->equals(*testIncohe), "Rozdielne po zmene 1. bytu");
		testIncohe->assign(*copyCohe);
		SimpleTest::assertTrue(copyCohe->equals(*testIncohe), "Rovnake nakonci");

		delete testIncohe;
		delete copyCohe;
	}
	ScenarMatrix::ScenarMatrix(const char* nazov)
		:SimpleTest(nazov)
	{

	}
	void ScenarMatrix::testScenar(int r, int c, double ppr, double ppc, double ppa)
	{
		srand(time(0));
		Milliseconds cTime(0);
		Milliseconds iTime(0);
		auto Cohe = new structures::CoherentMatrix<int>(r,c);
		auto Incohe = new structures::IncoherentMatrix<int>(r, c);
		for (long i = 0; i < r ; i++) {
			for (long j = 0; j < c; j++)
			{
				Cohe->at(i, j) = 1;
				Incohe->at(i, j) = 1;
			}
		}


		long pocet = 0;
		long pr = 0;
		long pc = 0;
		long pa = 0;
		do {
			
			switch ((rand()%3))
			{
			case 0:
				if (pr < (1000000 * ppr)) {
					SimpleTest::startStopwatch();
					Cohe->getRowCount();
					SimpleTest::stopStopwatch();
					cTime += SimpleTest::getElapsedTime();

					SimpleTest::startStopwatch();
					Incohe->getRowCount();
					SimpleTest::stopStopwatch();
					iTime += SimpleTest::getElapsedTime();

					pr++;
					pocet++;
				}
				break;
			case 1:
				if (pc < (1000000 * ppc)) {
				SimpleTest::startStopwatch();
				Cohe->getColumnCount();
				SimpleTest::stopStopwatch();
				cTime += SimpleTest::getElapsedTime();

				SimpleTest::startStopwatch();
				Incohe->getColumnCount();
				SimpleTest::stopStopwatch();
				iTime += SimpleTest::getElapsedTime();

				pc++;
				pocet++;
				}
				break;
			case 2:
				if (pa < (1000000 * ppa)) {
				int indexR = rand() % r;
				int indexC = rand() % c;
				SimpleTest::startStopwatch();
				Cohe->at(indexR, indexC);
				SimpleTest::stopStopwatch();
				cTime += SimpleTest::getElapsedTime();

				SimpleTest::startStopwatch();
				Incohe->at(indexR, indexC);
				SimpleTest::stopStopwatch();
				iTime += SimpleTest::getElapsedTime();

				pa++;
				pocet++;
				}
				break;
			default:
				break;
			}
			
		} while (pocet != 1000000);
		structures::Logger::getInstance().logDuration(r * c, cTime, "Dåžka trvania test Coherent matrix " + SimpleTest::getName());
		structures::Logger::getInstance().logDuration(r * c, iTime, "Dåžka trvania test Incoherent matrix " + SimpleTest::getName());
		delete Cohe;
		delete Incohe;
	}
	
	ScenarA::ScenarA() :
		ScenarMatrix("ScenarA")
	{
		
	}

	void ScenarA::test()
	{
		ScenarMatrix::testScenar(10, 50, 0.5, 0.5, 0);
	}

	ScenarB::ScenarB():
		ScenarMatrix("Scenar B")
	{
	}

	void ScenarB::test()
	{
		ScenarMatrix::testScenar(2000, 500, 0.5, 0.5, 0);
	}

	ScenarC::ScenarC()
		:ScenarMatrix("Scenar C")
	{
	}

	void ScenarC::test()
	{
		ScenarMatrix::testScenar(50, 10, 0.5, 0.5, 0);
	}

	ScenarD::ScenarD()
		:ScenarMatrix("Scenar D")
	{
	}

	void ScenarD::test()
	{
		ScenarMatrix::testScenar(500, 2000, 0.5, 0.5, 0);
	}

	

	Zlozitosti::Zlozitosti() :SimpleTest ("Casove zlozistosti")
	{
	}

	void Zlozitosti::test()
	{
		srand(time(0));
		
		int pm=0;
		int pn=0;
		for (size_t k = 1; k < 1000; k+=100)
		{
			Milliseconds cnTime(0);
			Milliseconds inTime(0);
			Milliseconds cmTime(0);
			Milliseconds imTime(0);

			Milliseconds AcnTime(0);
			Milliseconds AinTime(0);
			Milliseconds AcmTime(0);
			Milliseconds AimTime(0);

			auto Cohe1 = new structures::CoherentMatrix<int>(k, 100);
			auto Incohe1 = new structures::IncoherentMatrix<int>(k, 100);
			auto Cohe2 = new structures::CoherentMatrix<int>(100, k);
			auto Incohe2 = new structures::IncoherentMatrix<int>(100, k);

			auto other1 = new structures::CoherentMatrix<int>(k, 100);
			auto other2 = new structures::IncoherentMatrix<int>(k, 100);
			auto other3 = new structures::CoherentMatrix<int>(100, k);
			auto other4 = new structures::IncoherentMatrix<int>(100, k);

			//naplnenienie poli
			for (size_t i = 0; i < Incohe1->getRowCount(); i++) {
				for (size_t j = 0; j < Incohe1->getColumnCount(); j++)
				{
					Cohe1->at(i, j) = 1;
					Incohe1->at(i, j) = 1;
					other1->at(i, j) = i + j;
					other2->at(i, j) = i + j;
				}
			}
			for (size_t i = 0; i < Incohe2->getRowCount(); i++) {
				for (size_t j = 0; j < Incohe2->getColumnCount(); j++)
				{
					Cohe2->at(i, j) = 1;
					Incohe2->at(i, j) = 1;
					other3->at(i, j) = i + j;
					other4->at(i, j) = i + j;
				}
			}

			for (size_t i = 0; i < 100; i++)
			{
			// meni m
			
			
			 pm = rand() % Cohe1->getRowCount();
			 pn = rand() % Cohe1->getColumnCount();
			SimpleTest::startStopwatch();
			Cohe1->at(pm, pn);
			SimpleTest::stopStopwatch();
			cmTime += SimpleTest::getElapsedTime();
			
			SimpleTest::startStopwatch();
			Incohe1->at(pm,pn);
			SimpleTest::stopStopwatch();
			imTime += SimpleTest::getElapsedTime();

			//meni n
			 pm = rand() % Cohe2->getRowCount();
			 pn = rand() % Cohe2->getColumnCount();
			SimpleTest::startStopwatch();
			Cohe2->at(pm, pn);
			SimpleTest::stopStopwatch();
			cnTime += SimpleTest::getElapsedTime();

			SimpleTest::startStopwatch();
			Incohe2->at(pm, pn);
			SimpleTest::stopStopwatch();
			inTime += SimpleTest::getElapsedTime();
			//Assign n
			SimpleTest::startStopwatch();
			Cohe1->assign(*other1);
			SimpleTest::stopStopwatch();
			AcmTime += SimpleTest::getElapsedTime();

			SimpleTest::startStopwatch();
			Incohe1->assign(*other2);
			SimpleTest::stopStopwatch();
			AimTime += SimpleTest::getElapsedTime();
			//assign m
			SimpleTest::startStopwatch();
			Cohe2->assign(*other3);
			SimpleTest::stopStopwatch();
			AcnTime += SimpleTest::getElapsedTime();

			SimpleTest::startStopwatch();
			Incohe2->assign(*other4);
			SimpleTest::stopStopwatch();
			AinTime += SimpleTest::getElapsedTime();

			}
			structures::Logger::getInstance().logDuration(Cohe1->getColumnCount() * Cohe1->getRowCount(), cmTime/100, "Dåžka trvania test at Coherent n sa meni " + SimpleTest::getName());
			structures::Logger::getInstance().logDuration(Incohe1->getColumnCount() * Incohe1->getRowCount(), imTime/100, "Dåžka trvania test at Incoherent n sa meni " + SimpleTest::getName());
			structures::Logger::getInstance().logDuration(Cohe2->getColumnCount() * Cohe2->getRowCount(), cnTime/100, "Dåžka trvania test at Coherent m sa meni " + SimpleTest::getName());
			structures::Logger::getInstance().logDuration(Incohe2->getColumnCount() * Incohe2->getRowCount(), inTime/100, "Dåžka trvania test at Incoherent m sa meni " + SimpleTest::getName());

			structures::Logger::getInstance().logDuration(Cohe1->getColumnCount() * Cohe1->getRowCount(), AcmTime / 100, "Dåžka trvania test assign Coherent n sa meni " + SimpleTest::getName());
			structures::Logger::getInstance().logDuration(Incohe1->getColumnCount() * Incohe1->getRowCount(), AimTime / 100, "Dåžka trvania test assign Incoherent n sa meni " + SimpleTest::getName());
			structures::Logger::getInstance().logDuration(Cohe2->getColumnCount() * Cohe2->getRowCount(), AcnTime / 100, "Dåžka trvania test assign Coherent m sa meni " + SimpleTest::getName());
			structures::Logger::getInstance().logDuration(Incohe2->getColumnCount() * Incohe2->getRowCount(), AinTime/100, "Dåžka trvania test assign Incoherent m sa meni " + SimpleTest::getName());


			delete Cohe1;
			delete Incohe1;
			delete Cohe2;
			delete Incohe2;

			delete other1;
			delete other2;
			delete other3;
			delete other4;
		}
	}



	ScenarE::ScenarE() : SimpleTest ("Scenar E")
	{
	}

	void ScenarE::test()
	{
		//k = 2 m meni
		for (size_t i = 1; i < 100; i += 10)
		{
			auto Cohe = new structures::CoherentMatrix<int>(i, i);
			for (int j = 0; j < i; j++)
			{
				for (int k = 0; k < i; k++) {
					Cohe->at(j, k) = j + k;
				}
			}
			Milliseconds Ctime(0);
			auto COther = new structures::CoherentMatrix<int>(i, i);
			auto POMCohe = new structures::CoherentMatrix<int>(i, i);

			COther->assign(*Cohe);
			for (size_t m = 0; m < i; m++)
			{
				for (size_t n = 0; n < i; n++) {
					size_t pom =0;

					for (size_t o = 0; o < i; o++)
					{
						pom += COther->at(m, o) * Cohe->at(o, n);
					}

					POMCohe->at(m, n) = pom;
				}
			}
			COther->assign(*POMCohe);

			SimpleTest::stopStopwatch();
			structures::Logger::getInstance().logDuration(Cohe->getColumnCount() * Cohe->getRowCount(), SimpleTest::getElapsedTime(), "Coherent 2 mocnina" + SimpleTest::getName());
			delete Cohe;
			delete COther;
			delete POMCohe;
		}


		for (size_t i = 1; i < 100; i += 10)
		{

			auto Incohe = new structures::IncoherentMatrix<int>(i, i);
			for (size_t j = 0; j < i; j++)
			{
				for (size_t k = 0; k < i; k++) {
					Incohe->at(j, k) = j + k;
				}
			}
			Milliseconds Ctime(0);
			auto IOther = new structures::IncoherentMatrix<int>(i, i);
			auto POMI = new structures::IncoherentMatrix<int>(i, i);

			IOther->assign(*Incohe);
			for (size_t m = 0; m < i; m++)
			{
				for (size_t n = 0; n < i; n++) {
					size_t pom =0;

					for (size_t o = 0; o < i; o++)
					{
						pom += IOther->at(m, o) * Incohe->at(o, n);
					}

					POMI->at(m, n) = pom;
				}
			}
			IOther->assign(*POMI);

			SimpleTest::stopStopwatch();
			structures::Logger::getInstance().logDuration(Incohe->getColumnCount() * Incohe->getRowCount(), SimpleTest::getElapsedTime(), "Incoherent 2 mocnina" + SimpleTest::getName());
			delete Incohe;
			delete IOther;
			delete POMI;
		}
		

		// meni k

		size_t t = 20;
		Milliseconds cas(0);

		auto Cohe = new structures::CoherentMatrix<int>(t, t);
		Milliseconds Ctime(0);
		auto COther = new structures::CoherentMatrix<int>(t, t);
		auto POMCohe = new structures::CoherentMatrix<int>(t, t);
		for (size_t j = 0; j < t; j++)
		{
			for (size_t k = 0; k < t; k++) {
				Cohe->at(j, k) = j + k;
			}
		}
		for (size_t k = 1; k <= 10; k++)
		{
			SimpleTest::startStopwatch();
			if (k == 1) {
				COther->assign(*Cohe);

			}
			else {
				for (size_t m = 0; m < t; m++)
				{
					for (size_t n = 0; n < t; n++) {
						size_t pom = 0;

						for (size_t o = 0; o < t; o++)
						{
							pom += COther->at(m, o) * Cohe->at(o, n);
						}

						POMCohe->at(m, n) = pom;
						
					}
				}
				COther->assign(*POMCohe);
			}
		
			SimpleTest::stopStopwatch();	
			cas += SimpleTest::getElapsedTime();
			structures::Logger::getInstance().logDuration(k, cas , "Coherent k mocnina" + SimpleTest::getName());

		}
		delete Cohe;
		delete COther;
		delete POMCohe;

		Milliseconds cas2(0);
		auto Incohe = new structures::IncoherentMatrix<int>(t, t);
		Milliseconds Itime(0);
		auto IOther = new structures::IncoherentMatrix<int>(t, t);
		auto POMI = new structures::IncoherentMatrix<int>(t, t);
		for (size_t j = 0; j < t; j++)
		{
			for (size_t k = 0; k < t; k++) {
				Incohe->at(j, k) = j + k;
			}

		}
		
		for (size_t k = 1; k <= 10; k++)
		{
			SimpleTest::startStopwatch();
			if (k == 1) {
				IOther->assign(*Incohe);

			}
			else {
				for (size_t m = 0; m < t; m++)
				{
					for (size_t n = 0; n < t; n++) {
						size_t pom = 0;

						for (size_t o = 0; o < t; o++)
						{
							pom += IOther->at(m, o) * Incohe->at(o, n);
						}

						POMI->at(m, n) = pom;
					}
				}
				IOther->assign(*POMI);
			}
			SimpleTest::stopStopwatch();
			cas2 += SimpleTest::getElapsedTime();
			structures::Logger::getInstance().logDuration(k, cas2, "Incoherent k mocnina " + SimpleTest::getName());

		}
		delete Incohe;
		delete IOther;
		delete POMI;
	}
	
	};

