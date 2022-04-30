#include "list_test.h"
#include "../../structures/list/array_list.h"
#include <iostream>
#include <iostream>
using namespace structures;

namespace tests
{
// ListTestInterface:

	ListTestInterface::ListTestInterface(std::string name) :
		SimpleTest(std::move(name))
	{
	}

	void ListTestInterface::test()
	{
		int x = 0;
		structures::List<int>* list = this->makeList();
		list->add(x);
		list->assign(*list);
		list->clear();
		delete list->getBeginIterator();
		delete list->getEndIterator();
		list->getIndexOf(x);
		list->insert(x, x);
		list->isEmpty();
		list->operator[](0);
		list->removeAt(0);
		list->size();
		list->tryRemove(x);
		delete list;
		this->logPass("Compiled.");
	}

// ArrayListTestInterface:

	ArrayListTestInterface::ArrayListTestInterface() :
		ListTestInterface("Interface")
	{
	}

	structures::List<int>* ArrayListTestInterface::makeList() const
	{
		return new structures::ArrayList<int>();
	}




// LinkedListTestInterface:

	LinkedListTestInterface::LinkedListTestInterface() :
		ListTestInterface("Interface")
	{
	}

	structures::List<int>* LinkedListTestInterface::makeList() const
	{
		return new structures::LinkedList<int>();
	}

// ArrayListTestOverall:

	ArrayListTestOverall::ArrayListTestOverall() :
		ComplexTest("ArrayList")
	{
		addTest(new ArrayListTestInterface());
		addTest(new ArrayListTest());
	}

// LinkedListTestOverall:

	LinkedListTestOverall::LinkedListTestOverall() :
		ComplexTest("LinkedList")
	{
		addTest(new LinkedListTestInterface());
	}

//ZADANIE 2
	DoubleLinkedListTestOverall::DoubleLinkedListTestOverall() :
		ComplexTest("uloha 1")
	{
		addTest(new ArrayListTest());
		addTest(new DoubleLinkedListTest());
	}

	Scenar::Scenar() :
		ComplexTest("Uloha 2")
	{
		addTest(new AScenar());
		addTest(new BScenar());
		addTest(new CScenar());
	}
	ZlozitostiListy::ZlozitostiListy() 
		:ComplexTest("Uloha 3")
	{
		addTest(new Insert());
		addTest(new At());
		addTest(new RemoveAt());
	}

// ListTestOverall:

	ListTestOverall::ListTestOverall() :
		ComplexTest("List")
	{
		addTest(new ArrayListTestOverall());
		addTest(new LinkedListTestOverall());
	}
	ArrayListTest::ArrayListTest() :
		SimpleTest("ArrayList test Insert")
	{

	}
	void ArrayListTest::test()
	{

		auto arraylist = new ArrayList<int>;
		arraylist->add(10);
		arraylist->add(20);
		arraylist->add(30);
		arraylist->add(40);
		assertTrue(arraylist->size() == 4, "Velkost array");
		arraylist->add(100);
		arraylist->add(200);
		arraylist->add(300);
		arraylist->add(400);
		assertTrue(arraylist->size() == 8, "Testujem add");
		for (int i = 0; i < 9; i++) {
			arraylist->insert(1, 0);
		}
		assertTrue(arraylist->size() == 17, "Testujem insert");
		arraylist->insert(7, 0);
		arraylist->insert(77, 4);
		arraylist->insert(777, 18);
		arraylist->insert(7777, 20);
		assertTrue(arraylist->size() == 21, "Testujem insert");
	
		assertTrue(arraylist->at(0) == 7 , "Je 7");
		for (int i = 1; i < 4; i++)
		{
			assertTrue(arraylist->at(i) == 1, "Je 1");
		}
		assertTrue(arraylist->at(4) == 77, "Je 77");
		for (int i = 5; i < 11; i++)
		{
			assertTrue(arraylist->at(i) == 1, "Je 1");
		}
		assertTrue(arraylist->at(11) == 10, "Je 10");
		assertTrue(arraylist->at(12) == 20, "Je 20");
		assertTrue(arraylist->at(13) == 30, "Je 30");
		assertTrue(arraylist->at(14) == 40, "Je 40");
		assertTrue(arraylist->at(15) == 100, "Je 100");
		assertTrue(arraylist->at(16) == 200, "Je 200");
		assertTrue(arraylist->at(17) == 300, "Je 300");

		assertTrue(arraylist->at(18) == 777, "Je 777");
		assertTrue(arraylist->at(19) == 400, "Je 400");
		assertTrue(arraylist->at(20) == 7777, "Je 7777");


		auto otherDLL = new ArrayList<int>(*arraylist);
		SimpleTest::assertTrue(arraylist->equals(*otherDLL), "Testujem copyConstructor");
		arraylist->at(0) = 10;
		SimpleTest::assertFalse(arraylist->equals(*otherDLL), "Testujem equals");
		arraylist->assign(*otherDLL);
		SimpleTest::assertTrue(arraylist->equals(*otherDLL), "Testujem Assign");

		arraylist->tryRemove(1);
		assertTrue(arraylist->size() == 20, "Testujem tryRemove");

		arraylist->removeAt(18);
		assertTrue(arraylist->size() == 19, "Testujem RomoveAt");

		assertTrue(otherDLL->getIndexOf(10) == 11, "Testujem getIndexOf");
		arraylist->clear();
		assertTrue(arraylist->size() == 0, "Testujem clear");
		delete(otherDLL);

		delete arraylist;
	}
//------------------------------------------------------------------------

	DoubleLinkedListTest::DoubleLinkedListTest() :
		SimpleTest("DoubleLinkedList test Insert")
	{

	}
	void DoubleLinkedListTest::test()
	{
		auto DLL = new structures::DoubleLinkedList<int>();
		DLL->add(10);
		DLL->add(20);
		DLL->add(30);
		DLL->add(40);
		assertTrue(DLL->size() == 4, "testujem add");
		DLL->add(100);
		DLL->add(200);
		DLL->add(300);
		DLL->add(400);
		assertTrue(DLL->size() == 8, "testujem add");
		for (int i = 0; i < 9; i++) {
			DLL->insert(1, 0);
		}
		assertTrue(DLL->size() == 17, "testujem insert");
		DLL->insert(7, 0);
		DLL->insert(77, 4);
		DLL->insert(777, 18);
		DLL->insert(7777, 20);
		assertTrue(DLL->size() == 21, "testujem insert");

		assertTrue(DLL->at(0) == 7, "Je 7");
		for (int i = 1; i < 4; i++)
		{
			assertTrue(DLL->at(i) == 1, "Je 1");
		}
		assertTrue(DLL->at(4) == 77, "Je 77");
		for (int i = 5; i < 11; i++)
		{
			assertTrue(DLL->at(i) == 1, "Je 1");
		}
		assertTrue(DLL->at(11) == 10, "Je 10");
		assertTrue(DLL->at(15) == 100, "Je 100");
		assertTrue(DLL->at(18) == 777, "Je 777");
		assertTrue(DLL->at(19) == 400, "Je 400");
		assertTrue(DLL->at(20) == 7777, "Je 7777");
		//----------------------------------------
		auto otherDLL = new DoubleLinkedList<int>(*DLL);
		SimpleTest::assertTrue(DLL->equals(*otherDLL), "Testujem copyConstructor");
		DLL->at(0) = 10;
		SimpleTest::assertFalse(DLL->equals(*otherDLL), "Testujem equals");
		DLL->assign(*otherDLL);
		SimpleTest::assertTrue(DLL->equals(*otherDLL), "Testujem Assign");

		DLL->tryRemove(1);
		assertTrue(DLL->size() == 20, "Testujem tryRemove");

		DLL->removeAt(18);
		assertTrue(DLL->size() == 19, "Testujem RomoveAt");

		assertTrue(otherDLL->getIndexOf(10) == 11, "Testujem getIndexOf");
		DLL->clear();
		assertTrue(DLL->size() == 0 , "Testujem clear");
		delete(otherDLL);
		delete DLL;
	}
	Scenare::Scenare(const char* nazov) 
		: SimpleTest(nazov)
	{
	}
	void Scenare::testScenar(double ppi, double ppr, double ppa, double ppg)
	{
		srand(time(0));
		Milliseconds aTime(0);
		Milliseconds lTime(0);
		auto array = new ArrayList<int>();
		auto doublik = new DoubleLinkedList<int>();

		for (int i = 0; i < 50000; i++)
		{
			array->add(rand()%100);
			doublik->add(rand()%100);
		}

		long pocet = 0;
		long pi = 0;
		long pr = 0;
		long pa = 0;
		long pg = 0;
		int kam;
		do {
			int kam = rand() % array->size();
			
			switch ((rand() % 4))
			{
			case 0:
				if (pi < (100000 * ppi)) {
					SimpleTest::startStopwatch();
					array->insert(1,kam);
					SimpleTest::stopStopwatch();
					aTime += SimpleTest::getElapsedTime();

					SimpleTest::startStopwatch();
					doublik->insert(1, kam);
					SimpleTest::stopStopwatch();
					lTime += SimpleTest::getElapsedTime();

					pi++;
					pocet++;
				}
				break;
			case 1:
				if (pr < (100000 * ppr)) {
					SimpleTest::startStopwatch();
					array->removeAt(kam);
					SimpleTest::stopStopwatch();
					aTime += SimpleTest::getElapsedTime();

					SimpleTest::startStopwatch();
					doublik->removeAt(kam);
					SimpleTest::stopStopwatch();
					lTime += SimpleTest::getElapsedTime();

					pr++;
					pocet++;
				}
				break;
			case 2:
				if (pa < (100000 * ppa)) {
					SimpleTest::startStopwatch();
					array->at(kam);
					SimpleTest::stopStopwatch();
					aTime += SimpleTest::getElapsedTime();

					SimpleTest::startStopwatch();
					doublik->at(kam);
					SimpleTest::stopStopwatch();
					lTime += SimpleTest::getElapsedTime();

					pa++;
					pocet++;
				}
				break;
			case 3:
				kam = rand() % 100;
				if (pg < (100000 * ppg)) {
					SimpleTest::startStopwatch();
					array->getIndexOf(kam);
					SimpleTest::stopStopwatch();
					aTime += SimpleTest::getElapsedTime();

					SimpleTest::startStopwatch();
					doublik->getIndexOf(kam);
					SimpleTest::stopStopwatch();
					lTime += SimpleTest::getElapsedTime();

					pg++;
					pocet++;
				}
				break;
			default:
				break;
			}

		} while (pocet != 100000);
		structures::Logger::getInstance().logDuration( array->size(), aTime, "Dåžka trvania arraylist - " + SimpleTest::getName());
		structures::Logger::getInstance().logDuration(doublik->size(), lTime, "Dåžka trvania doublelinkedlist - " + SimpleTest::getName());
		delete array;
		delete doublik;
	}
	AScenar::AScenar():
		Scenare("Scenar A")
	{
	}
	void AScenar::test()
	{
		Scenare::testScenar(0.2, 0.2, 0.5, 0.1);
	}
	BScenar::BScenar():
		Scenare("Scenar B")
	{
	}
	void BScenar::test()
	{
		Scenare::testScenar(0.35, 0.35, 0.2, 0.10);
	}
	CScenar::CScenar():
		Scenare("Scenar C")
	{
	}
	void CScenar::test()
	{
		Scenare::testScenar(0.45, 0.45, 0.05, 0.05);
	}
	
	
	
	Insert::Insert() :SimpleTest("Insert")
	{
	}

	void Insert::test()
	{
		srand(time(0));
		for (int k = 0; k < 1000000; k += 100)
		{
			auto array = new ArrayList<int>();
			
			for (int i = 0; i <= k; i++)
			{
				array->add(i);
			}
			SimpleTest::startStopwatch();
			array->insert(1, 0);
			SimpleTest::stopStopwatch();

			Logger::getInstance().logDuration(array->size(), SimpleTest::getElapsedTime(), "Dåžka trvania arrayList Insert");
			delete array;
		}
		for (int k = 0; k < 1000000; k += 100)
		{
			auto dl = new DoubleLinkedList<int>();
			
			for (int i = 0; i <= k; i++)
			{
				dl->add(i);
			}
			SimpleTest::startStopwatch();
			dl->insert(1, dl->size()/2);
			SimpleTest::stopStopwatch();

			Logger::getInstance().logDuration(dl->size(), SimpleTest::getElapsedTime(), "Dåžka trvania doubleLinkedList Insert");
			delete dl;
		}
	}

	At::At() :SimpleTest("At")
	{
	}

	void At::test()
	{
		srand(time(0));
		for (int k = 0; k < 1000000; k += 100)
		{
			auto array = new ArrayList<int>();

			for (int i = 0; i <= k; i++)
			{
				array->add(i);
			}
			SimpleTest::startStopwatch();
			array->at(0);
			SimpleTest::stopStopwatch();

			Logger::getInstance().logDuration(array->size(), SimpleTest::getElapsedTime(), "Dåžka trvania arrayList At");
			delete array;
		}
		for (int k = 0; k < 1000000; k += 100)
		{
			auto dl = new DoubleLinkedList<int>();

			for (int i = 0; i <= k; i++)
			{
				dl->add(i);
			}
			SimpleTest::startStopwatch();
			dl->at(dl->size() / 2);
			SimpleTest::stopStopwatch();

			Logger::getInstance().logDuration(dl->size(), SimpleTest::getElapsedTime(), "Dåžka trvania doubleLinkedList At");
			delete dl;
		}
	}

	RemoveAt::RemoveAt() :SimpleTest("RemoveAt")
	{
	}

	void RemoveAt::test()
	{srand(time(0));
		for (int k = 0; k < 1000000; k += 100)
		{
			auto array = new ArrayList<int>();

			for (int i = 0; i <= k; i++)
			{
				array->add(i);
			}
			SimpleTest::startStopwatch();
			array->removeAt(0);
			SimpleTest::stopStopwatch();

			Logger::getInstance().logDuration(array->size(), SimpleTest::getElapsedTime(), "Dåžka trvania arrayList RemoveAt");
			delete array;
		}
		for (int k = 0; k < 1000000; k += 100)
		{
			auto dl = new DoubleLinkedList<int>();

			for (int i = 0; i <= k; i++)
			{
				dl->add(i);
			}
			SimpleTest::startStopwatch();
			dl->removeAt(dl->size() / 2);
			SimpleTest::stopStopwatch();

			Logger::getInstance().logDuration(dl->size(), SimpleTest::getElapsedTime(), "Dåžka trvania doubleLinkedList RemoveAt");
			delete dl;
		}

	}
	
}