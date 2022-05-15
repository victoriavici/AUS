#include "table_test.h"
#include "../../structures/table/binary_search_tree.h"
#include "../../structures/table/hash_table.h"
#include "../../structures/table/linked_table.h"
#include "../../structures/table/sorted_sequence_table.h"
#include "../../structures/table/table.h"
#include "../../structures/table/treap.h"
#include "../../structures/table/unsorted_sequence_table.h"

namespace tests
{
	TableTestInterface::TableTestInterface() :
		SimpleTest("Interface")
	{
	}

	void TableTestInterface::test()
	{
		int x = 0;
		structures::Table<int, int>* table = this->makeTable();
		table->equals(*table);
		table->assign(*table);
		table->insert(0, 0);
		table->find(0);
		table->remove(0);
		table->tryFind(0, x);
		table->containsKey(0);
		delete table;
		this->logPass("Compiled.");
	}

	structures::Table<int, int>* BinarySearchTreeTestInterface::makeTable()
	{
		return new structures::BinarySearchTree<int, int>();
	}

	structures::Table<int, int>* HashTableTestInterface::makeTable()
	{
		return new structures::HashTable<int, int>();
	}

	structures::Table<int, int>* LinkedTableTestInterface::makeTable()
	{
		return new structures::LinkedTable<int, int>();
	}

	structures::Table<int, int>* SortedSequenceTableTestInterface::makeTable()
	{
		return new structures::SortedSequenceTable<int, int>();
	}

	structures::Table<int, int>* TreapTestInterface::makeTable()
	{
		return new structures::Treap<int, int>();
	}

	structures::Table<int, int>* UnsortedSequenceTableTestInterface::makeTable()
	{
		return new structures::UnsortedSequenceTable<int, int>();
	}

	BinarySearchTreeTestOverall::BinarySearchTreeTestOverall() :
		ComplexTest("BinarySearchTree")
	{
		addTest(new BinarySearchTreeTestInterface());
	}

	HashTableTestOverall::HashTableTestOverall() :
		ComplexTest("HashTable")
	{
		addTest(new HashTableTestInterface());
	}

	LinkedTableTestOverall::LinkedTableTestOverall() :
		ComplexTest("LinkedTable")
	{
		addTest(new LinkedTableTestInterface());
	}

	SortedSequenceTableTestOverall::SortedSequenceTableTestOverall() :
		ComplexTest("SortedSequenceTable")
	{
		addTest(new SortedSequenceTableTestInterface());
	}

	TreapTestOverall::TreapTestOverall() :
		ComplexTest("Treap")
	{
		addTest(new TreapTestInterface());
	}

	UnsortedSequenceTableTestOverall::UnsortedSequenceTableTestOverall() :
		ComplexTest("UnsortedSequenceTable")
	{
		addTest(new UnsortedSequenceTableTestInterface());
	}

	TableTestOverall::TableTestOverall() :
		ComplexTest("Table")
	{
		addTest(new BinarySearchTreeTestOverall());
		addTest(new HashTableTestOverall());
		addTest(new LinkedTableTestOverall());
		addTest(new SortedSequenceTableTestOverall());
		addTest(new TreapTestOverall());
		addTest(new UnsortedSequenceTableTestOverall());
	}
	TableTest::TableTest() : 
		ComplexTest("Uloha 1")
	{
		addTest(new BST());
		addTest(new SST());
	}
	BST::BST() :
		SimpleTest("Binary Search Tree")
	{
	}
	void BST::test()
	{
		auto strom = new structures::BinarySearchTree<int, int>();
		strom->insert(1, 10);
		strom->insert(2, 20);
		strom->insert(5, 30);
		strom->insert(4, 40);
		assertTrue(strom->size() == 4, "Velkost");

		strom->insert(10, 1);
		strom->insert(9, 2);
		strom->insert(8, 3);
		strom->insert(7, 4);
		assertTrue(strom->size() == 8, "Velkost");

		

		auto other = new structures::BinarySearchTree<int, int>(*strom);
		assertTrue(strom->equals(*other), "Testujem copy");

		strom->remove(8);
		assertTrue(strom->size() == 7, "Testujem remove");
		strom->remove(10);
		strom->remove(4);
		strom->remove(5);
		strom->remove(2);
		
	strom->clear();
		assertTrue(strom->isEmpty(), "Testujem clear a empty");

		delete other;
		delete strom;


	}
	SST::SST() :
		SimpleTest("Sorted Sequence Table")
	{
	}
	void SST::test()
	{
		auto table = new structures::SortedSequenceTable<int, int>();
		table->insert(6, 10);
		table->insert(2, 20);
		table->insert(5, 30);
		table->insert(4, 40);
		assertTrue(table->size() == 4, "Velkost");

		table->insert(10, 1);
		table->insert(9, 2);
		table->insert(8, 3);
		table->insert(7, 4);
		table->insert(0, 100);
		assertTrue(table->size() == 9, "Velkost");


		auto other = new structures::SortedSequenceTable<int, int>(*table);
		assertTrue(table->equals(*other), "Testujem copy");

		table->remove(8);
		assertTrue(table->size() == 8, "Testujem remove");
		table->remove(0);

		table->clear();
		assertTrue(table->isEmpty(), "Testujem clear a empty");

		delete other;
		delete table;
	}

	ScenareTable::ScenareTable(const char* nazov) :
		SimpleTest(nazov)
	{
	}
	void ScenareTable::testScenar(double ppi, double ppr, double ppt)
	{
		srand(time(0));
		Milliseconds aTime(0);
		Milliseconds lTime(0);
		auto sst = new structures::SortedSequenceTable<int,int>();
		auto bst = new structures::BinarySearchTree<int,int>();
		
		


		long pocet;
		long pi=0;
		long pr = 0;
		long pt = 0;
		int kam;
		int kluc;
		int data;
		int pom;
		for (int i = 0; i < 5; i++)
		{
		
			for (int i = 0; i < 40000; i++)
			{
				do {
					kluc = (rand() * rand()) % 100001;
				} while (sst->containsKey(kluc));
				sst->insert(kluc, kluc);
				bst->insert(kluc, kluc);

			}

			pocet = 0;
			pi = 0;
			pr = 0;
			pt = 0;
			kam;
		
			do {
		
				switch ((rand() % 3))
				{
				case 0:
					if (pi < (100000 * ppi)) {

						do {
							kluc = (rand() * rand()) % 100001;
						} while (sst->containsKey(kluc));

						SimpleTest::startStopwatch();
						sst->insert(kluc, pocet);
						SimpleTest::stopStopwatch();
						aTime += SimpleTest::getElapsedTime();

						SimpleTest::startStopwatch();
						bst->insert(kluc, pocet);
						SimpleTest::stopStopwatch();
						lTime += SimpleTest::getElapsedTime();

						pi++;
						pocet++;
					}
					break;
				case 1:
					if (pr < (100000 * ppr)) {
						do {
							kluc = (rand() * rand()) % 100001;
						} while (!sst->containsKey(kluc));

						SimpleTest::startStopwatch();
						sst->remove(kluc);
						SimpleTest::stopStopwatch();
						aTime += SimpleTest::getElapsedTime();

						SimpleTest::startStopwatch();
						bst->remove(kluc);
						SimpleTest::stopStopwatch();
						lTime += SimpleTest::getElapsedTime();

						pr++;
						pocet++;
					}
					break;
				case 2:
					if (pt < (100000 * ppt)) {
						kluc = (rand() * rand()) % 100001;
						data = 0;
						SimpleTest::startStopwatch();
						sst->tryFind(kluc, data);
						SimpleTest::stopStopwatch();
						aTime += SimpleTest::getElapsedTime();

						SimpleTest::startStopwatch();
						bst->tryFind(kluc,data);
						SimpleTest::stopStopwatch();
						lTime += SimpleTest::getElapsedTime();

						pt++;
						pocet++;
					}
					break;
				default:
					break;
				}
				
				//structures::Logger::getInstance().logInfo(std::to_string(pocet));
			} while (pocet != 100000);
			
			sst->clear();
			bst->clear();
		}
		structures::Logger::getInstance().logDuration(sst->size(), aTime/5 , "Priemerna dåžka trvania Sorted Sequence Table - " + SimpleTest::getName());
		structures::Logger::getInstance().logDuration(bst->size(), lTime/5 , "Priemerná dåžka trvania Binary Search Tree - " + SimpleTest::getName());
		delete sst;
		delete bst;
	}

	ScenarTA::ScenarTA() :
		ScenareTable("Scenar A")
	{
	}
	void ScenarTA::test()
	{
		ScenareTable::testScenar(0.2, 0.2, 0.6);
	}
	ScenarTB::ScenarTB() :
		ScenareTable("Scenar B")
	{
	}
	void ScenarTB::test()
	{
		ScenareTable::testScenar(0.4, 0.4, 0.2);
	}
	
	ScenareSpustacTable::ScenareSpustacTable() :
		ComplexTest("Uloha 2")
	{
		addTest(new ScenarTA());
		addTest(new ScenarTB());
	}



	TryFind::TryFind():SimpleTest("TryFind")
	{
	}
	void TryFind::test()
	{
		

		int p = 1;
		/*srand(time(0));
		auto sst = new structures::SortedSequenceTable<int,int>();
		
		for (int k = 0; k < 1000000; k+=1000)
		{
			
			for (int i = p; i < k; i++)
			{
				sst->insert(i, i);
			}
			p = k;
			Milliseconds cas(0);
			for (int i = 0; i < 10; i++)
			{
				SimpleTest::startStopwatch();
				int data = 0;
				sst->tryFind(0, data);
				SimpleTest::stopStopwatch();
				cas += SimpleTest::getElapsedTime();
			}
			structures::Logger::getInstance().logDuration(sst->size(),cas/10, "Dåžka trvania SST tryFind");
		}
		delete sst;*/

	/*	
		int max = 0;
		for (int k = 1000; k < 100000; k += 1000)
		{
			auto bst = new structures::BinarySearchTree<int, int>();
			bst->insert(k, 1);

			for (int i = 1; i < k; i += 10)
			{
				do {
					p = rand() % i;
				} while (bst->containsKey(p));
				bst->insert(p, p);
				if (p > max) 
					max = p;
				
			}
			if (!bst->containsKey(0))
				bst->insert(0, 0);
			
			SimpleTest::startStopwatch();
			int data = 0;
			bst->tryFind(0,data);
			SimpleTest::stopStopwatch();

			structures::Logger::getInstance().logDuration(bst->size(), SimpleTest::getElapsedTime(), "Dåžka trvania BST tryFind");
			delete bst;

		}
		*/

		auto bst = new structures::BinarySearchTree<int, int>();
		int min = INT_MAX;
		 p = 0;
		for (size_t i = 0; i < 1000; i++)
		{
			for (size_t j = 0; j < 100; j++)
			{
				do
				{
					p = ((rand() % 1000) * (rand() % 1000));
				} while (bst->containsKey(p));
				bst->insert(p, p);
				if (p < min)
					min = p;
			}
			Milliseconds time(0);
			for (size_t j = 0; j < 10; j++)
			{
				SimpleTest::startStopwatch();
				bst->tryFind(min,min);
				SimpleTest::stopStopwatch();
				time += SimpleTest::getElapsedTime();
				
			}
			structures::Logger::getInstance().logDuration(bst->size(), time/10, "Dåžka trvania BST remove");
		}
		delete bst;

	
	}	
	
	Remove::Remove() :SimpleTest("Remove")
	{
		
	}
	void Remove::test()
	{
		srand(time(0));
		for (int k = 10000; k <= 1010000; k += 100000)
		{
			auto sst = new structures::SortedSequenceTable<int, int>();

			for (int i = 0; i <= k; i++)
			{
				sst->insert(i, i);
			}
			SimpleTest::startStopwatch();
			sst->remove(0);
			SimpleTest::stopStopwatch();

			structures::Logger::getInstance().logDuration(sst->size(), SimpleTest::getElapsedTime(), "Dåžka trvania sst remove");
			delete sst;
		}

		

		//auto bst = new structures::BinarySearchTree<int, int>();
		//int min = INT_MAX;
		//int p = 0;
		//for (size_t i = 0; i < 1000; i++)
		//{
		//	for (size_t j = 0; j < 100; j++)
		//	{
		//		do
		//		{
		//			p = ((rand() % 1000) * (rand() % 1000));
		//		} while (bst->containsKey(p));
		//		bst->insert(p, p);
		//		if (p < min)
		//			min = p;
		//	}
		//	Milliseconds time(0);
		//	for (size_t j = 0; j < 10; j++)
		//	{
		//		SimpleTest::startStopwatch();
		//		bst->remove(min);
		//		SimpleTest::stopStopwatch();
		//		time += SimpleTest::getElapsedTime();
		//		bst->insert(min, min);
		//	}
		//	structures::Logger::getInstance().logDuration(bst->size(), time/10, "Dåžka trvania BST remove");
		//}
		//delete bst;
	}


	ZlozitostiTable::ZlozitostiTable():ComplexTest("Uloha 3")
	{
		addTest(new InsertT());
		addTest(new Remove());
		addTest(new TryFind());
	}
	InsertT::InsertT() :SimpleTest("Insert")
	{
	}
	void InsertT::test()
	{
		srand(time(0));
		for (int k = 10000; k <= 1010000; k += 100000)
		{
			auto sst = new structures::SortedSequenceTable<int, int>();

			for (int i = 1; i <= k; i++)
			{
				sst->insert(i, i);
			}
			SimpleTest::startStopwatch();
			sst->insert(0,0);
			SimpleTest::stopStopwatch();
			sst->remove(0);

			structures::Logger::getInstance().logDuration(sst->size(), SimpleTest::getElapsedTime(), "Dåžka trvania sst remove");
			delete sst;
		}

		/*srand(time(0));
		auto sst = new structures::SortedSequenceTable<int, int>();
		int pom = 10000000;
		for (int k = 9900000; k >= 0; k -= 100000)
		{

			for (int i = pom ; i > k; i--)
			{
				sst->insert(i, i);
			}
		
				SimpleTest::startStopwatch();
				sst->insert(k, k);
				SimpleTest::stopStopwatch();
				sst->remove(k);
				pom = 
				structures::Logger::getInstance().logDuration(sst->size(), SimpleTest::getElapsedTime(), "Dåžka trvania SST insert");

		}
		delete sst;*/

		/*
		int p;
		int min = INT_MAX;
		auto bst = new structures::BinarySearchTree<int, int>();
		for (int j = 100; j < 10000; j += 100) {

			for (int i = 0; i < 100; i++)
			{
				do {
					p = rand() % j;
				} while (bst->containsKey(p));
				bst->insert(p, p);
				if (p < min)
					min = p;
			}

			Milliseconds ltime(0);
			for (int i = 0; i < 10; i++)
			{
				SimpleTest::startStopwatch();
				bst->insert(min - 1, 1 );
				SimpleTest::stopStopwatch();
				bst->remove(min - 1);
				ltime += SimpleTest::getElapsedTime();
			}

			structures::Logger::getInstance().logDuration(bst->size(), ltime , "Dåžka trvania BST insert");
			
		}
		delete bst;*/
		

		auto bst = new structures::BinarySearchTree<int, int>();
		int min = INT_MAX;
		int p = 0;
		for (size_t i = 0; i < 1000; i++)
		{
			for (size_t j = 0; j < 100; j++)
			{
				do
				{
					p = ((rand() % 1000) * (rand() % 1000));
				} while (bst->containsKey(p));
				bst->insert(p, p);
				if (p < min)
					min = p;
			}
			Milliseconds time(0);
			for (size_t j = 0; j < 10; j++)
			{
				SimpleTest::startStopwatch();
				bst->insert(min-1, min-1);
				SimpleTest::stopStopwatch();
				time += SimpleTest::getElapsedTime();
				bst->remove(min - 1);

			}
			structures::Logger::getInstance().logDuration(bst->size(), time / 10, "Dåžka trvania BST insert");
		}
		delete bst;
	}
		

}
