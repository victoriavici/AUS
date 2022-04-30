#pragma once

#include "matrix.h"
#include <stdexcept>
#include "../../structures/heap_monitor.h"

namespace structures
{
	/// <summary> Implementacia matice v suvislej pamati. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v matici. </typepram>
	template<typename T>
	class CoherentMatrix
		: public Matrix<T>
	{
	public:
		/// <summary>
		///	Konstruktor. Vytvori maticu o danom pocte riadkov a stlpcov.
		/// Polozky su inicializovane na "nulovu" hodnotu typu T.
		/// </summary>
		/// <param name="rowCount"> Pocet riadkov. </param>
		/// <param name="columnCount"> Pocet stlpcov. </param>
		CoherentMatrix(size_t rowCount, size_t columnCount);

		/// <summary> Inicializuje tuto maticu ako kopiu matice odovzdanej ako parameter. </summary>
		/// <param name = "other"> Odkaz na maticu, z ktorej sa prevezmu vlastnosti. </param>
		CoherentMatrix(CoherentMatrix& other);

		/// <summary> Destruktor. </summary>
		~CoherentMatrix();

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
	/// <summary> Vektor s datami. </summary>
	Vector* vector_;
	/// <summary> Pocet prvkov v poli. </summary>
	int columns_;
	int rows_;
	size_t size_;

private:
	/// <summary> Mapovacia funkcia, ktora prevedie index v poli na index vo vektore. </summary>
	/// <param name = "index"> Index v poli. </param>
	/// <returns> Index vo vektore. </returns>
	int mapFunction(int row, int column) const;
};

	template<typename T>
	inline CoherentMatrix<T>::CoherentMatrix(size_t rowCount, size_t columnCount)
	{
		columns_ = columnCount;
		rows_ = rowCount;
		size_ = rowCount * columnCount;
		vector_ = new Vector(sizeof(T) * size_);
	
	}

	template<typename T>
	inline CoherentMatrix<T>::CoherentMatrix(CoherentMatrix& other) 
		
	{
		vector_ = new Vector(*(other.vector_));
		columns_ = other.columns_;
		rows_ = other.rows_;
		size_ = other.size_;
	}

	template<typename T>
	inline CoherentMatrix<T>::~CoherentMatrix()
	{
		vector_->~Vector();
		delete vector_; 
		vector_ = nullptr;
		size_ = 0;
		columns_ = 0;
		rows_ = 0;
	}

	template<typename T>
	inline Structure& CoherentMatrix<T>::assign(Structure& other)
	{
		if (this != &other) {
			CoherentMatrix<T>& cohe = dynamic_cast<CoherentMatrix<T>&>(other);
			if (size_ == cohe.size_ && rows_ == cohe.rows_ && columns_ == cohe.columns_) {
				vector_->assign(*cohe.vector_);
			}
			else {
				throw std::invalid_argument("Coherent size differ");
			}
		}

		return *this;

	}

	template<typename T>
	inline bool CoherentMatrix<T>::equals(Structure& other)
	{
		CoherentMatrix<T>* otherCohe = dynamic_cast<CoherentMatrix<T>*>(&other);
		if (this != otherCohe)
		{
			if (otherCohe != nullptr) {
				if (otherCohe->getRowCount() == rows_ && otherCohe->getColumnCount() == columns_) {
					for (size_t i = 0; i < rows_; i++)
						for (size_t j = 0; j < columns_; j++)
						{
							{
								if (otherCohe->at(i, j) != at(i, j)) {
									return false;
								}
							}
						}
					return true;
				}
			}
		}
		return false;
	}


	template<typename T>
	inline size_t CoherentMatrix<T>::size()
	{
		return columns_ * rows_;
	}

	template<typename T>
	inline size_t CoherentMatrix<T>::getRowCount()
	{
		return rows_;
	}

	template<typename T>
	inline size_t CoherentMatrix<T>::getColumnCount()
	{
		 return columns_;
	}

	template<typename T>
	inline T& CoherentMatrix<T>::at(int rowIndex, int columnIndex)
	{
		return *reinterpret_cast<T*>(vector_->getBytePointer(mapFunction(rowIndex, columnIndex)));
	}
	template<typename T>
	inline int CoherentMatrix<T>::mapFunction(int row, int column) const
	{
		Utils::rangeCheckExcept(row, rows_, "Invalid index of rows!");
		Utils::rangeCheckExcept(column, columns_, "Invalid index of columns!");
		return (row * columns_ + column) * sizeof(T);
	}
}