#include "priority_queue_test.h"
#include "../../structures/priority_queue/heap.h"
#include "../../structures/priority_queue/priority_queue_limited_sorted_array_list.h"
#include "../../structures/priority_queue/priority_queue_linked_list.h"
#include "../../structures/priority_queue/priority_queue_sorted_array_list.h"
#include "../../structures/priority_queue/priority_queue_two_lists.h"
#include "../../structures/priority_queue/priority_queue_unsorted_array_list.h"

namespace tests
{
    PriorityQueueTestInterface::PriorityQueueTestInterface() :
        SimpleTest("Interface")
    {
    }

    void PriorityQueueTestInterface::test()
    {
        int x = 0;
        structures::PriorityQueue<int>* queue = this->makePriorityQueue();
        queue->push(0, x);
        queue->peek();
        queue->peekPriority();
        queue->pop();
        queue->assign(*queue);
        delete queue;
        this->logPass("Compiled.");
    }

    structures::PriorityQueue<int>* PriorityQueueUnsortedArrayListTestInterface::makePriorityQueue()
    {
        return new structures::PriorityQueueUnsortedArrayList<int>();
    }

    structures::PriorityQueue<int>* PriorityQueueSortedArrayListTestInterface::makePriorityQueue()
    {
        return new structures::PriorityQueueSortedArrayList<int>();
    }

    structures::PriorityQueue<int>* PriorityQueueLimitedSortedArrayListTestInterface::makePriorityQueue()
    {
        return new structures::PriorityQueueLimitedSortedArrayList<int>();
    }

    structures::PriorityQueue<int>* PriorityQueueLinkedListTestInterface::makePriorityQueue()
    {
        return new structures::PriorityQueueLinkedList<int>();
    }

    structures::PriorityQueue<int>* PriorityQueueTwoListsTestInterface::makePriorityQueue()
    {
        return new structures::PriorityQueueTwoLists<int>();
    }

    structures::PriorityQueue<int>* HeapTestInterface::makePriorityQueue()
    {
        return new structures::Heap<int>();
    }

    PriorityQueueUnsortedArrayListTestOverall::PriorityQueueUnsortedArrayListTestOverall() :
        ComplexTest("PriorityQueueUnsortedArray")
    {
        addTest(new PriorityQueueUnsortedArrayListTestInterface());
    }

    PriorityQueueSortedArrayListTestOverall::PriorityQueueSortedArrayListTestOverall() :
        ComplexTest("PriorityQueueSortedArrayList")
    {
        addTest(new PriorityQueueSortedArrayListTestInterface());
    }

    PriorityQueueLimitedSortedArrayListTestOverall::PriorityQueueLimitedSortedArrayListTestOverall() :
        ComplexTest("PriorityQueueLimitedSortedArrayList")
    {
        addTest(new PriorityQueueLimitedSortedArrayListTestInterface());
    }

    PriorityQueueLinkedListTestOverall::PriorityQueueLinkedListTestOverall() :
        ComplexTest("PriorityQueueLinkedList")
    {
        addTest(new PriorityQueueLinkedListTestInterface());
    }

    PriorityQueueTwoListsTestOverall::PriorityQueueTwoListsTestOverall() :
        ComplexTest("PriorityQueueTwoLists")
    {
        addTest(new PriorityQueueTwoListsTestInterface());
        addTest(new PriorityQueueTwoListTest());
    }

    HeapTestOverall::HeapTestOverall() :
        ComplexTest("Heap")
    {
        addTest(new HeapTestInterface());
        addTest(new HeapTest());
    }

    PriorityQueueTestOverall::PriorityQueueTestOverall() :
        ComplexTest("PriorityQueue")
    {
        addTest(new PriorityQueueUnsortedArrayListTestOverall());
        addTest(new PriorityQueueSortedArrayListTestOverall());
        addTest(new PriorityQueueLimitedSortedArrayListTestOverall());
        addTest(new PriorityQueueLinkedListTestOverall());
        addTest(new PriorityQueueTwoListsTestOverall());
        addTest(new HeapTestOverall());
    }

    //1.uloha



    PriorityQueueTwoListTest::PriorityQueueTwoListTest() :
        SimpleTest("PriorityQueueTwoLists test")
    {
    }

    void PriorityQueueTwoListTest::test()
    {
        auto queue = new structures::PriorityQueueTwoLists<int>;
        queue->push(1, 1);
        queue->push(3, 2);
        queue->push(5, 3);
        queue->push(7, 4);

        assertTrue(queue->size() == 4, "Velkost queue");
        queue->push(2, 10);
        queue->push(4, 20);
        queue->push(6, 30);
        queue->push(8, 40);
        assertTrue(queue->size() == 8, "Testujem push");
       
         for (int i = 1; i < 4; i++)
        {
            queue->push(1, 100);
        }
        assertTrue(queue->size() == 11, "testujem");


        auto other = new structures::PriorityQueueTwoLists<int>(*queue);
        SimpleTest::assertTrue(queue->peek() == other->peek(), "Testujem copyConstructor");
        
        queue->clear();
        assertTrue(queue->size() == 0, "Testujem clear");
  
        delete other;
        delete queue;
    }

    HeapTest::HeapTest():
        SimpleTest("Heap test")
    {
    }

    void HeapTest::test()
    {
        auto heap = new structures::Heap<int>;
        heap->push(1, 1);
        heap->push(3, 2);
        heap->push(5, 3);
        heap->push(7, 4);

        assertTrue(heap->size() == 4, "Velkost queue");
        heap->push(2, 10);
        heap->push(4, 20);
        heap->push(6, 30);
        heap->push(8, 40);
        assertTrue(heap->size() == 8, "Testujem push");

       heap->pop();
        assertTrue(heap->size() == 7, "Testujem pop");
        assertTrue(heap->peek() == heap->pop(), "Testujem pop a peek");

         heap->push(1, 1);
        assertTrue(heap->size() == 7, "testujem");

        for (int i = 1; i < 4; i++)
        {
            heap->push(1, 100);
        }
        assertTrue(heap->size() == 10, "testujem");


        auto other = new structures::Heap<int>(*heap);
        SimpleTest::assertTrue(heap->peek() == other->peek(), "Testujem copyConstructor");

        heap->clear();
        assertTrue(heap->size() == 0, "Testujem clear");

        delete other;
        delete heap;
    
    }
    ScenareQueue::ScenareQueue(const char* nazov):
        SimpleTest(nazov)
    {
    }
    void ScenareQueue::testScenar(double ppu, double ppo, double ppe)
    {
        srand(time(0));
        Milliseconds aTime(0);
        Milliseconds lTime(0);
        auto heap = new structures::Heap<int>();
        auto two = new structures::PriorityQueueTwoLists<int>();

        for (int i = 0; i < 70000; i++)
        {
            heap->push(rand() % 100000 + 1, rand() % 100);
            two->push(rand() % 100000 + 1, rand() % 100);
        }

        long pocet = 0;
        long pu = 0;
        long po = 0;
        long pe = 0;
        int kam;
        do {
           

            switch ((rand() % 3))
            {
            case 0:
                if (pu < (100000 * ppu)) {
                    int priority = rand() % 100000 +1;
                    SimpleTest::startStopwatch();
                    heap->push(priority,pocet);
                    SimpleTest::stopStopwatch();
                    aTime += SimpleTest::getElapsedTime();

                    SimpleTest::startStopwatch();
                    two->push(priority, pocet);
                    SimpleTest::stopStopwatch();
                    lTime += SimpleTest::getElapsedTime();

                    pu++;
                    pocet++;
                }
                break;
            case 1:
                if (po < (100000 * ppo)) {
                    SimpleTest::startStopwatch();
                    heap->pop();
                    SimpleTest::stopStopwatch();
                    aTime += SimpleTest::getElapsedTime();

                    SimpleTest::startStopwatch();
                    two->pop();
                    SimpleTest::stopStopwatch();
                    lTime += SimpleTest::getElapsedTime();

                    po++;
                    pocet++;
                }
                break;
            case 2:
                if (pe < (100000 * ppe)) {
                    SimpleTest::startStopwatch();
                    heap->peek();
                    SimpleTest::stopStopwatch();
                    aTime += SimpleTest::getElapsedTime();

                    SimpleTest::startStopwatch();
                    two->peek();
                    SimpleTest::stopStopwatch();
                    lTime += SimpleTest::getElapsedTime();

                    pe++;
                    pocet++;
                }
                break;
            default:
                break;
            }

        } while (pocet != 100000);
        structures::Logger::getInstance().logDuration(heap->size(), aTime, "Dåžka trvania Heap - " + SimpleTest::getName());
        structures::Logger::getInstance().logDuration(two->size(), lTime, "Dåžka trvania PriorityQueueTwoLists - " + SimpleTest::getName());
        delete heap;
        delete two;
    
    }
  
    ScenarQA::ScenarQA() :
        ScenareQueue("Scenar A")
    {
    }
    void ScenarQA::test()
    {
        ScenareQueue::testScenar(0.35, 0.35, 0.3);
    }
    ScenarQB::ScenarQB() :
        ScenareQueue("Scenar B")
    {
    }
    void ScenarQB::test()
    {
        ScenareQueue::testScenar(0.5, 0.3, 0.2);
    } 
    ScenarQC::ScenarQC() :
        ScenareQueue("Scenar C")
    {
    }
    void ScenarQC::test()
    {
        ScenareQueue::testScenar(0.7, 0.25, 0.05);
    }
    ScenareSpustac::ScenareSpustac() :
        ComplexTest("Uloha 2")
    {
        addTest(new ScenarQA());
        addTest(new ScenarQB());
        addTest(new ScenarQC());
    }
    QueueTest::QueueTest():
        ComplexTest(" ")
    {
        addTest(new PriorityQueueTwoListTest());
        addTest(new HeapTest());
    }

    // Uloha 3

    ZlozitostiQueue::ZlozitostiQueue() 
        :ComplexTest("Uloha 3")
    {
        addTest(new Push());
        addTest(new Pop());
        addTest(new Peek());
    }
    Push::Push()
        :SimpleTest("Push")
    {
    }
    void Push::test()
    {
        srand(time(0));
        auto heap = new structures::Heap<int>();

        for (int i = 99; i >= 0; i--)
        {
            SimpleTest::startStopwatch();
            heap->push(i, i);
            SimpleTest::stopStopwatch();

            structures::Logger::getInstance().logDuration(heap->size(), SimpleTest::getElapsedTime(), "Dåžka trvania heap Push");
        }
        delete heap;
        
       
        auto two = new structures::PriorityQueueTwoLists<int>();
            

         for (int i = 99; i >= 0; i--)
         {
                   SimpleTest::startStopwatch();
                    two->push(i, i);
                    SimpleTest::stopStopwatch();

                    structures::Logger::getInstance().logDuration(two->size(), SimpleTest::getElapsedTime(), "Dåžka trvania priorityQueueTwoLists Push");
                }
            
            delete two;
        
    }
    Pop::Pop()
        :SimpleTest("Pop")
    {
    }
    void Pop::test()
    {

        srand(time(0));
        for (int k = 0; k < 1000000; k += 1000)
        {
            auto heap = new structures::Heap<int>();

            for (int i = 0; i <= k; i++)
            {
                heap->push(i,i);
            }
            SimpleTest::startStopwatch();
            heap->pop();
            SimpleTest::stopStopwatch();

            structures::Logger::getInstance().logDuration(heap->size(), SimpleTest::getElapsedTime(), "Dåžka trvania heap pop");
            delete heap;
        }
        for (int k = 0; k < 1000000; k += 1000)
        {
            auto two = new structures::PriorityQueueTwoLists<int>();

            for (int i = 0; i <= k; i++)
            {
                two->push(i,i);
            }
            SimpleTest::startStopwatch();
            two->pop();
            SimpleTest::stopStopwatch();

            structures::Logger::getInstance().logDuration(two->size(), SimpleTest::getElapsedTime(), "Dåžka trvania PriorityQueueTwoLists pop");
            delete two;
        }
    }
    Peek::Peek()
       :SimpleTest("Peek")
    {
    }
    void Peek::test()
    {
        srand(time(0));
        for (int k = 0; k < 1000000; k += 1000)
        {
            auto heap = new structures::Heap<int>();

            for (int i = 0; i <= k; i++)
            {
                heap->push(i,i);
            }
            SimpleTest::startStopwatch();
            heap->peek();
            SimpleTest::stopStopwatch();

            structures::Logger::getInstance().logDuration(heap->size(), SimpleTest::getElapsedTime(), "Dåžka trvania heap peek");
            delete heap;
        }
        for (int k = 0; k < 1000000; k += 1000)
        {
            auto two = new structures::PriorityQueueTwoLists<int>();

            for (int i = 0; i <= k; i++)
            {
                two->push(i,i);
            }
            SimpleTest::startStopwatch();
            two->peek();
            SimpleTest::stopStopwatch();

            structures::Logger::getInstance().logDuration(two->size(), SimpleTest::getElapsedTime(), "Dåžka trvania PriorityQueueTwoLists peek");
            delete two;
        }
    }
}