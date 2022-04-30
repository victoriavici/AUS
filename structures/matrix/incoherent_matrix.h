#pragma once

#include "matrix.h"
#include <stdexcept>
#include "../../structures/heap_monitor.h"

namespace structures
{
	/// <summary> Implementacia matice v nesuvislej pamati. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v matici. </typepram>
	template<typename T>
	class IncoherentMatrix
		: public Matrix<T>
	{
	public:
		/// <summary>
		///	Konstruktor. Vytvori maticu o danom pocte riadkov a stlpcov.
		/// Polozky su inicializovane na "nulovu" hodnotu typu T.
		/// </summary>
		/// <param name="rowCount"> Pocet riadkov. </param>
		/// <param name="columnCount"> Pocet stlpcov. </param>
		IncoherentMatrix(size_t rowCount, size_t columnCount);

		/// <summary> Inicializuje tuto maticu ako kopiu matice odovzdanej ako parameter. </summary>
		/// <param name = "other"> Odkaz na maticu, z ktorej sa prevezmu vlastnosti. </param>
		IncoherentMatrix(IncoherentMatrix& other);

		/// <summary> Destruktor. </summary>
		~IncoherentMatrix();

		/// <summary>
		/// Ak je to mozne (parametrom je matica, ktora ma rovnake rozmery ako ako aktualna matica),
		/// tak skopiruje vlastnosti z matice odovzdanej ako parameter.
		/// Ak to nie je mozne, vyhodi sa vynimka.
		/// </summary>
		/// <param name = "other"> Odkaz na strukturu, z ktorej maju prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
		Structure& assign(Structure& other) override;

		/// <summary>
		/// Ak je parametrom matica a obsah porovnavanych matic je rovnaky,
		/// tak vrati hodnotu true. V opacnom pripade vrati hodnotu false.
		/// </summary>
		/// <param name="other"> Odkaz na strukturu, s ktorou sa ma tato matica porovnat. </param>
		/// <returns>True ak su struktury zhodne typom aj obsahom. </returns>
		bool equals(Structure& other) override;

		/// <summary> Pocet vsetkych prvkov v matici. </summary>
		/// <returns> Pocet prvkov v matici. </returns>
		size_t size() override;

		/// <summary> Vrati pocet riadkov v matici. </summary>
		/// <returns> Pocet riadkov matice. </returns>
		size_t getRowCount() override;

		/// <summary> Vrati pocet stlpcov matice. </summary>
		/// <returns> Pocet stlpcov matice. </returns>
		size_t getColumnCount() override;

		/// <summary> Vrati odkaz na prvok v danom riadku a stlpci. </summary>
		/// <param name="rowIndex"> Index riadku. </param>
		/// <param name="columnIndex"> Index stlpca. </param>
		/// <returns> Odkaz na prvok na danych indexoch. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index riadku alebo stlpca nepatri do matice. </exception>
		T& at(int rowIndex, int columnIndex) override;
	
private:
	Array<Array<T>*>* array_;
	size_t rows_;
	size_t columns_;
	};

	template<typename T>
	inline IncoherentMatrix<T>::IncoherentMatrix(size_t rowCount, size_t columnCount)
	{
		array_ = new Array<Array<T>*>(rowCount);
		for (size_t i = 0; i < rowCount; i++)
		{
			array_ ->at(i) = new Array<T>(columnCount);
		}
		rows_ = rowCount;
		columns_ = columnCount;
	}

	template<typename T>
	inline IncoherentMatrix<T>::IncoherentMatrix(IncoherentMatrix& other)
	{
		
		rows_ = other.rows_;
		columns_ = other.columns_;
		array_ = new Array<Array<T>*>(rows_);
		for (size_t i = 0; i < rows_; i++)
		{
			array_->at(i) = new Array<T>(*other.array_->at(i));
		}
	}

	template<typename T>
	inline IncoherentMatrix<T>::~IncoherentMatrix()
	{
		for (size_t i = 0; i < rows_; i++)
		{
			delete array_->at(i);
		}
		delete array_;
		array_ = nullptr;
		rows_ = 0;
		columns_ = 0;
	}

	template<typename T>
	inline Structure& IncoherentMatrix<T>::assign(Structure& other)
	{
		if (this != &other) {
			auto incohe = dynamic_cast<IncoherentMatrix<T>&>(other);
			if (rows_ == incohe.rows_ && columns_ == incohe.columns_) {
				
				for (size_t i = 0; i < rows_; i++) {
					array_->at(i)->assign(*incohe.array_->at(i));
				}
			}
			else {
				throw std::invalid_argument("size differ");
			}
		}
		return *this;
	}

	template<typename T>
	inline bool IncoherentMatrix<T>::equals(Structure& other)
	{
		if (&other != this) {
			auto otherCohe = dynamic_cast<IncoherentMatrix<T>*>(&other);
			if (otherCohe->columns_ == columns_ && otherCohe->rows_ == rows_) {

				for (size_t i = 0; i < rows_; i++) {
					for (size_t j = 0; j < columns_; j++) {
						if (otherCohe->at(i,j) != this->at(i,j)) {
							//delete otherCohe;
							return false;
						}
					}
				}
			}
			else {
				//delete otherCohe;
				return false;
			}
		}
		return true;
	}

	template<typename T>
	inline size_t IncoherentMatrix<T>::size()
	{
		return rows_ * columns_;
	}

	template<typename T>
	inline size_t IncoherentMatrix<T>::getRowCount()
	{
		return rows_;
	}

	template<typename T>
	inline size_t IncoherentMatrix<T>::getColumnCount()
	{
		return columns_;
	}

	template<typename T>
	inline T& IncoherentMatrix<T>::at(int rowIndex, int columnIndex)
	{

		Utils::rangeCheckExcept(rowIndex, rows_, "Invalid index of rows!");
		Utils::rangeCheckExcept(columnIndex, columns_, "Invalid index of columns!");
		return array_->at(rowIndex)->at(columnIndex);
	}
};