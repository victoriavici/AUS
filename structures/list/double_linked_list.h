#pragma once

#include "list.h"
#include "linked_list.h"

namespace structures
{
    // implementacne tipy: 
    //  - namiesto triedy List<T> mozete v triede DoubleLinkedList<T> 
    //    zdedit jednostranne zretazeny zoznam (LinkedList<T>).
    //    ak tak urobite, mozete mnoho metod odstranit a prekryt iba tie, 
    //    ktore maju z pohladu obojsmerne zretazeneho zoznamu vyznam a
    //    zvysok nechat na predka.
    //  - nezabudnite si vytvorit triedu pre prvok obojstranne zretazeneho zoznamu.
    //    opat tento prvok mozete zdedit z prvku jednostranne zretazeneho zoznamu.
    //  - ak vyuzijete dedicnost, budete moct vyuzit predkove iteratory, 
    //    takze ich nebudete musiet implementovat.

    /// <summary> Obojstranne zretazeny zoznam. </summary>
    /// <typeparam name = "T"> Typ dat ukladanych v zozname. </typepram>
    /// 
    
    template<typename T>
    class DoubleLinkedListItem : public LinkedListItem<T>
    {
   

    public: 
        DoubleLinkedListItem(T Data);
        DoubleLinkedListItem(DoubleLinkedListItem<T>& other);
        ~DoubleLinkedListItem();
    
        DoubleLinkedListItem<T>* getPrevious();
        void setPrevious(DoubleLinkedListItem<T>* previous);

    private:
        DoubleLinkedListItem<T>* previous_;
    };


	template<typename T>
	class DoubleLinkedList : public LinkedList<T> 
	{
    public:
        
    DoubleLinkedListItem<T>* getItemAtIndex(int index);
    DoubleLinkedListItem<T>* createItem(T Data);
    void connect(DoubleLinkedListItem<T>* item1, DoubleLinkedListItem<T>* item2);

	};

    //DATA-LINKED-LIST-ITEM//
    template<typename T>
    inline DoubleLinkedListItem<T>::DoubleLinkedListItem(T Data) :
        DataItem<T>(Data),
        next_(nullptr),
        previous_(nullptr)
    {
    }

    template<typename T>
    inline DoubleLinkedListItem<T>::DoubleLinkedListItem(DoubleLinkedListItem<T>& other) :
        DataItem<T>(other),
        next_(other.next_),
        previous_(other.previous_)
    {
    }

    template<typename T>
    inline DoubleLinkedListItem<T>::~DoubleLinkedListItem()
    {
        next_ = nullptr;
        previous_ = nullptr;
    }

    template<typename T>
    inline DoubleLinkedListItem<T>* DoubleLinkedListItem<T>::getPrevious()
    {
        return previous_;
    }

    template<typename T>
    inline void DoubleLinkedListItem<T>::setPrevious(DoubleLinkedListItem<T>* previous)
    {
        previous_ = previous;
    }
   
    template<typename T>
    inline DoubleLinkedListItem<T>* DoubleLinkedList<T>::getItemAtIndex(int index)
    {
        if (index == this->size() - 1)
        {
            return last_;
        }
        if (index == 0)
        {
            return first_;
        }

        if (index > 0) {
            if (this->size() - index > index) {
                auto current = this->first_;
                for (size_t i = 0; i <= index; i++)
                {
                    current = current->getNext();
                }
                return current;
            }
            else {
                auto current = this->last_;
                for (size_t i = size_-1; i > index; i--)
                {
                    current = current->getPrevious();
                }
                return current;
            }
        }
    }

    template<typename T>
    inline DoubleLinkedListItem<T>* DoubleLinkedList<T>::createItem(T Data)
    {
        return new DoubleLinkedListItem<T>(Data);
    }

    

    template<typename T>
    inline void DoubleLinkedList<T>::connect(DoubleLinkedListItem<T>* item1, DoubleLinkedListItem<T>* item2)
    {
        item1->setNext(item2);
        item2->setPrevious(item1);
    }
}