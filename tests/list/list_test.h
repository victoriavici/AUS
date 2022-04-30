#pragma once

#include "../test.h"
#include "../../structures/list/array_list.h"
#include "../../structures/list/linked_list.h"
#include"../../structures/list/double_linked_list.h"

namespace tests
{
	/// <summary>
	/// Zavola vsetky metody z rozhrania listu avsak nekontroluje ich spravnost.
	/// Zabezpeci, ze vsetky metody budu prelozene kompilatorom.
	/// </summary>
	class ListTestInterface
		: public SimpleTest
	{
	public:
		ListTestInterface(std::string name);
		void test() override;

	protected:
		virtual structures::List<int>* makeList() const = 0;
	};

	/// <summary>
	/// Zavola vsetky metody ArrayListu.
	/// </summary>
	class ArrayListTestInterface
		: public ListTestInterface
	{
	public:
		ArrayListTestInterface();

	protected:
		structures::List<int>* makeList() const override;
	};

	class ArrayListTest
		:public SimpleTest
	{
	public:
		ArrayListTest();
		void test() override;
	};

	/// <summary>
	/// Zavola vsetky metody LinkedListu.
	/// </summary>
	class LinkedListTestInterface
		: public ListTestInterface
	{
	public:
		LinkedListTestInterface();

	protected:
		structures::List<int>* makeList() const override;
	};

	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju ArrayList.
	/// </summary>
	class ArrayListTestOverall
		: public ComplexTest
	{
	public:
		ArrayListTestOverall();
	};

	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju LinkedList.
	/// </summary>
	class LinkedListTestOverall
		: public ComplexTest
	{
	public:
		LinkedListTestOverall();
	};

	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju ArrayList a LinkedList.
	/// </summary>
	class ListTestOverall :
		public ComplexTest
	{
	public:
		ListTestOverall();
	};




	class DoubleLinkedListTestOverall
		: public ComplexTest
	{
	public:
		DoubleLinkedListTestOverall();
	};

	class DoubleLinkedListTest
		:public SimpleTest
	{
	public:
		DoubleLinkedListTest();
		void test() override;
	};

	///uloha 2
	class Scenare :
		public SimpleTest {
	public:

		Scenare(const char* nazov);
		void testScenar(double ppi, double ppr, double ppa, double ppg);
	};

	class AScenar :
		public Scenare {
	public:
		AScenar();
		void test() override;
	};
	class BScenar :
		public Scenare {
	public:
		BScenar();
		void test() override;
	};
	class CScenar :
		public Scenare {
	public:
		CScenar();
		void test() override;
	};
	class Scenar
		: public ComplexTest
	{
	public:
		Scenar();
	};

	//uloha 3
	class ZlozitostiListy :
		public ComplexTest {
	public:
		ZlozitostiListy();
	};
	class Insert :
		public SimpleTest {
	public:
		Insert();
		void test() override;
	};
	class At :
		public SimpleTest {
	public:
		At();
		void test() override;
	};
	class RemoveAt :
		public SimpleTest {
	public:
		RemoveAt();
		void test() override;
	};

}