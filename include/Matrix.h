#ifndef MATRIX_H
#define MATRIX_H

#include <initializer_list>
#include <vector>
#include <iostream>
#include <string>
#include "Vector.h"

namespace AlgLib {

    /** \brief The Matrix class, which stores a rectangular Matrix
    * \param T The type of the objects to be stored in each entry of the Matrix.
    */
	template<typename T>
	class Matrix {

	public:
	    template <typename S>
	    friend std::ostream& operator<<(std::ostream& out, const Matrix<S>& m);
	    /** \brief Constructor that takes in row and column. Entries are set to 0.
	    * \param row The number of rows the matrix has.
	    * \param column The number of columns the matrix has.
        */
		Matrix(int row, int column);
		/** \brief Constructor that takes in a 2D-vector
		* \param theMatrix Each vector should be a row vector. That means that theMatrix[0] should be
		*        the first row of the matrix
		*/
		Matrix(const std::vector< std::vector<T> >& theMatrix);

		/** \brief Constructor that takes in a std::vector of AlgLib:vector<T>
		* \param theMatrix Each std::vector should be a row vector. That means theMatrix[0] should be the first row of the Matrix
		*/
		Matrix(const std::vector< AlgLib::Vector<T> >& theMatrix);

		/** \brief Constructor that takes in an initializer list.
		* \param m The initializer list. See Matrix::Matrix(const std::vector< std::vector<T> >& theMatrix) for how to format.
		* \throw std::invalid_argument Throws this exception if the provided initializer lists dimensions are inconsistent
		*/
		Matrix(std::initializer_list<std::initializer_list<T> > m); // Probably should add more constructors later

		/**
		* \brief Copy constructor
		* \param rhs The Matrix object to be copied
		*/
		Matrix(const Matrix& rhs);

		/**
		* \brief Accesses the row vector
		* \param row The row number in the Matrix. The first row is numbered 0
		* \return A std::vector<T> reference to the row vector. Note that assignment can be done. Use with caution. An element can be accessed like [1][2].
		*/
		virtual std::vector<T>& operator[](int row); // Only row because we can't nest it from this class. The vector class can take care of the other

		/**
		* \brief Multiplies two matrices
		*/
		virtual Matrix operator*(const Matrix& other) const;
		/**
		* \brief Adds two matrices
		*/
		virtual Matrix operator+(const Matrix& other) const;
		/**
		* \brief Subtracts two matrices
		*/
		virtual Matrix operator-(const Matrix& other) const;
		/*
		* Pushing implementation until later - 7/18/16 Jonathan Xia
		virtual Matrix inverse();
		virtual Matrix transpose();
		virtual int determinant();
		*/

		/**

		*/
		virtual Matrix transpose() const;
        /** \brief Returns the matrix in vector form
        * \return A nested std::vector of AlgLib::Vector<T>. Each element of the outer vector is a row vector. So, `getRowVectors()[0]` would be the first row of the
        matrix as a AlgLib::Vector<T>
        */
		virtual std::vector< AlgLib::Vector<T> > getRowVectors() const;

		/** \brief Returns the matrix in column vectors
		* \return An std::vector of AlgLib::Vector<T>. Each element of the outer vector is a column AlgLib::Vector<T>. So, `getColumnVectors()[0]` would be the first column of the Matrix
		*/
		virtual std::vector< AlgLib::Vector<T> > getColumnVectors() const;

		/** \brief Sets the value of an entry in the matrix
		* \param row The row number of the entry. Note that numbering starts at 0, so the first row is numbered 0
		* \param col The column number of the entry. Numbering starts at 0.
		* \param value The value that the entry will take on
		*/
		virtual void setValue(int row, int col, T value);
		/** \brief Gets the value of an entry in the matrix
		* \param row The row number of the entry to be accessed. Numbering starts at 0, so the first row is numbered 0.
		* \param col The column number of the entry to be accessed. Numbering starts at 0.
		* \return The value at Matrix[row][col]
		*/
		virtual T getValue(int row, int col) const;
		/** \brief Gives the number of rows in the Matrix.
		* \return The number of rows in the Matrix
		*/
		virtual int numRows() const;
		/** \brief Gives the number of columns in the Matrix.
		* \return The number of columns in the Matrix
		*/
		virtual int numColumns() const;

		/** \brief Returns the determinant of the Matrix
		*
		* \return The determinant of the Matrix object. Requires the +, -, and * operators to be defined for the entries.
		* \throw not_square_matrix Throws this exception if the Matrix is not square (has the same number of rows and columns)
		*/
		virtual T det() const;

		/** \brief Gives the minor of the Matrix at entry i, j
		*
		* A minor of an entry i, j is the Matrix that results when the i-th row and the j-th column are deleted.
		* This can be used to evaluate determinants.
		*/
		virtual Matrix<T> getMinor(int i, int j) const;

	    /** \brief Adds a row to the bottom of the Matrix */
        virtual void addRow();
        /** \brief Adds a column to the right of the Matrix */
        virtual void addColumn();

	private:
		std::vector< AlgLib::Vector<T> > mMatrix;
		int rows;
		int columns;
	};
}

#include "../src/Matrix/Matrix.inl"

#endif