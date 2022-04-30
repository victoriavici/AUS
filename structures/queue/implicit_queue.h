#pragma once

#include "queue.h"
#include "../array/array.h"

#include <stdexcept>

namespace structures
{
	/// <summary> Implicitny front. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych vo fronte. </typepram>
	template<typename T>
	class ImplicitQueue : public Queue<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		ImplicitQueue();

		/// <summary> Parametricky konstruktor. </summary>
		/// <param name = "capacity"> Maximalna velkost frontu. </param>
		ImplicitQueue(size_t capacity);

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Implicitny front, z ktoreho sa prevezmu vlastnosti. </param>
		ImplicitQueue(ImplicitQueue<T>& other);

		/// <summary> Destruktor. </summary>
		~ImplicitQueue();

		/// <summary> Vrati pocet prvkov vo fronte. </summary>
		/// <returns> Pocet prvkov vo fronte. </returns>
		size_t size() override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Front, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento front nachadza po priradeni. </returns>
		Structure& assign(Structure& other) override;

		/// <summary> Porovnanie struktur. </summary>
		/// <param name="other">Struktura, s ktorou sa ma tato struktura porovnat. </param>
		/// <returns>True ak su struktury zhodne typom aj obsahom. </returns>
		bool equals(Structure& other) override;

		/// <summary> Vymaze front. </summary>
		void clear() override;

		/// <summary> Prida prvok do frontu. </summary>
		/// <param name = "data"> Pridavany prvok. </param>
		/// <exception cref="std::out_of_range"> Vyhodena, ak je front plny. </exception>
		void push(const T& data) override;

		/// <summary> Odstrani prvok z frontu. </summary>
		/// <returns> Prvok na zaciatku frontu. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak je front prazdny. </exception>
		T pop() override;

		/// <summary> Vrati prvok na zaciatku frontu. </summary>
		/// <returns> Prvok na zaciatku frontu. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak je front prazdny. </exception>
		T& peek() override;

	protected:
		/// <summary> Pole, pomocou ktoreho je implementovany front. </summary>
		Array<T>* array_;

		/// <summary> Index prveho prvku vo fronte. </summary>
		int startIndex_;

		/// <summary> Pocet prvkov vo fronte. </summary>
		size_t size_;
	};

	template<typename T>
	ImplicitQueue<T>::ImplicitQueue() :
		ImplicitQueue(10)
	{
	}

	template<typename T>
	ImplicitQueue<T>::ImplicitQueue(size_t capacity) :
		Queue<T>(),
		array_(new Array<T>(capacity)),
		startIndex_(0),
		size_(0)
	{
	}

	template<typename T>
	ImplicitQueue<T>::ImplicitQueue(ImplicitQueue<T>& other) :
		Queue<T>(other),
		array_(new Array<T>(*other.array_)),
		startIndex_(other.startIndex_),
		size_(other.size_)
	{
	}

	template<typename T>
	ImplicitQueue<T>::~ImplicitQueue()
	{
		delete array_;
		array_ = nullptr;
		clear();
	}

	template<typename T>
	inline Structure& ImplicitQueue<T>::assign(Structure& other)
	{
		if (this != &other) {
			auto otherQueue = dynamic_cast<ImplicitQueue<T>&>(other);
			array_->assign(*otherQueue.array_);
			size_ = otherQueue.size();
			startIndex_ = otherQueue.startIndex_;
		}
		return *this;
	}

	template<typename T>
	size_t ImplicitQueue<T>::size()
	{
		return size_;
	}

	template<typename T>
	inline bool ImplicitQueue<T>::equals(Structure& other)
	{
		if (this != &other) {
			auto otherQ = dynamic_cast<ImplicitQueue<T>*>(&other);
			if (size_ != otherQ->size())
			{
				return false;
			}
			for (size_t i = startIndex_, j = otherQ->startIndex_, count = 0; count < size_; i = (i + 1) % array_->size(), j = (j + 1) % array_->size(), count++) {
				if (array_->at(i) != otherQ->array_->at(j)) {
					return false;
				}
			}
		}
		return true;
		
	}


	template<typename T>
	inline void ImplicitQueue<T>::clear()
	{
		size_ = 0;
		startIndex_ = 0;

	}

	template<typename T>
	inline void ImplicitQueue<T>::push(const T& data)
	{
		if (size_ != array_->size()) {
			array_->at((startIndex_ + size_) % array_->size()) = data;
			size_++;
		}
		else {
			std::range_error("Queue is full!!");
		}
	}

	template<typename T>
	inline T ImplicitQueue<T>::pop()
	{
		if (size_ != 0)
		{
			size_--;
			startIndex_ = (startIndex_ + 1) % array_->size();
			return array_->at(startIndex_);
		}
		throw std::logic_error("Implicit queue is empty");
	}

	template<typename T>
	inline T& ImplicitQueue<T>::peek()
	{
		if (size_ != 0) {
			return array_->at(startIndex_);
		} 
		throw std::logic_error("Implicit queue is empty");
	}
}