#pragma once

#include "priority_queue_list.h"
#include "../list/array_list.h"
#include "../utils.h"
#include <stdexcept>

namespace structures
{
	/// <summary> Prioritny front implementovany haldou. Implementujucim typom haldy je struktura ArrayList. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v prioritnom fronte. </typepram>
	template<typename T>
	class Heap : public PriorityQueueList<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		Heap();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Halda, z ktorej sa prevezmu vlastnosti. </param>
		Heap(Heap<T>& other);

		/// <summary> Priradenie struktury. </summary>
		/// <param name = "other"> Struktura, z ktorej ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
		Structure& assign(Structure& other) override;

		/// <summary> Vlozi prvok s danou prioritou do haldy. </summary>
		/// <param name = "priority"> Priorita vkladaneho prvku. </param>
		/// <param name = "data"> Vkladany prvok. </param>
		void push(int priority, const T& data) override;

		/// <summary> Odstrani prvok s najvacsou prioritou z haldy. </summary>
		/// <returns> Odstraneny prvok. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je halda prazdna. </exception>
		T pop() override;

	protected:
		/// <summary> Vrati index v ArrayList-e, na ktorom sa nachadza prvok s najvacsou prioritou. </summary>
		/// <returns> Index prvku s najvacsou prioritou. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je ArrayList prazdny. </exception>
		int indexOfPeek() override;

	private:
		/// <summary> Vrati index v ArrayList-e, na ktorom by sa mal nachadzat otec daneho prvku. </summary>
		/// <param name = "index"> Index prvku, ktoreho otca chceme vratit. </param>
		/// <returns> Index, na ktorom ba sa mal nachadzat otec prvku. </returns>
		int getParentIndex(int index);

		/// <summary> Vrati index v ArrayList-e, na ktorom by mal mat dany prvok syna s najvacsou prioritou. </summary>
		/// <param name = "index"> Index prvku, ktoreho syna chceme vratit. </param>
		/// <returns> Index, na ktorom by sa mal nachadzat syn prvku. </returns>
		int getGreaterSonIndex(int index);
	};

	template<typename T>
	Heap<T>::Heap() :
		PriorityQueueList<T>(new ArrayList<PriorityQueueItem<T>*>())
	{
	}

	template<typename T>
	Heap<T>::Heap(Heap<T>& other) :
		Heap<T>()
	{
		assign(other);
	}

	template<typename T>
	inline Structure& Heap<T>::assign(Structure& other)
	{
		return PriorityQueueList<T>::assignPrioQueueList(dynamic_cast<Heap<T>&>(other));
	}

	template<typename T>
	void Heap<T>::push(int priority, const T& data)
	{
		PriorityQueueList<T>::list_->add(new PriorityQueueItem<T>(priority, data));

		int indexCurrent = PriorityQueueList<T>::list_->size() - 1;
		int indexParent = getParentIndex(indexCurrent);

		while (indexCurrent != 0 && PriorityQueueList<T>::list_->at(indexCurrent)->getPriority() < PriorityQueueList<T>::list_->at(indexParent)->getPriority())
		{
			Utils::swap(PriorityQueueList<T>::list_->at(indexCurrent), PriorityQueueList<T>::list_->at(indexParent));

			indexCurrent = indexParent;
			indexParent = getParentIndex(indexCurrent);
		}
	}

	template<typename T>
	T Heap<T>::pop()
	{
		int index = PriorityQueueList<T>::indexOfPeek();
		if (index != -1) {
			int indexLast = list_->size() - 1;

			if (index != indexLast) {
				Utils::swap(PriorityQueueList<T>::list_->at(index), PriorityQueueList<T>::list_->at(indexLast));
			}
			
			auto item = list_->removeAt(indexLast);
			T data = item->accessData();
			delete item;

			//upratovanie
			//PriorityQueueList<T>::list_->add(new PriorityQueueItem<T>(index, data));

			int index = 0;
			int indexSon = getGreaterSonIndex(index);

			while (indexSon != -1 && PriorityQueueList<T>::list_->at(index)->getPriority() > PriorityQueueList<T>::list_->at(indexSon)->getPriority())
			{
				Utils::swap(PriorityQueueList<T>::list_->at(index), PriorityQueueList<T>::list_->at(indexSon));

				index = indexSon;
				indexSon = getGreaterSonIndex(index);
			}
			//

			return data;
		}
		else {
			throw std::logic_error("Priority queue is empty");
		}
	}

	template<typename T>
	inline int Heap<T>::getParentIndex(int index)
	{
		return (index - 1) / 2;
	}

	template<typename T>
	inline int Heap<T>::getGreaterSonIndex(int index)
	{
		int indexLeft = 2 * index + 1;
		int indexRight = 2 * index + 2;
		int size = PriorityQueueList<T>::list_->size();

		if (indexLeft >= size) {
			return -1;
		}
		else {
			if (indexRight >= size) {
				return indexLeft;
			}
			else {
				return PriorityQueueList<T>::list_->at(indexLeft)->getPriority() < PriorityQueueList<T>::list_->at(indexRight)->getPriority() ? indexLeft : indexRight;
			}
		}
	}

	template<typename T>
	inline int Heap<T>::indexOfPeek()
	{
		return Structure::isEmpty() ? -1 : 0;
	}
}