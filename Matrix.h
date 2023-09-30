//
// Created by loris on 30/09/2023.
//

#ifndef LIGHTNN_MATRIX_H
#define LIGHTNN_MATRIX_H
#include "vector.h"

template <typename T> class Matrix {
private:
    T *values = nullptr;
	vector<unsigned int> dimensions;

	vector<unsigned int> cursor;

	bool isEmpty() const;
	void enlarge(bool vertically, bool horizontally);

public:
	Matrix();
	Matrix(vector<unsigned int> dimensions);
	Matrix(unsigned int rows, unsigned int columns);
	Matrix(unsigned int rows, unsigned int columns, T* values);
	Matrix(const Matrix& matrix);

	~Matrix();

	T& at(unsigned int row, unsigned int column);
	

	Matrix<T> transpose() const;

	void addColumn(T* values = nullptr);
	void addRow(T* values = nullptr);

	Matrix<T> operator=(const Matrix<T>& matrix);
	Matrix<T> operator*(const Matrix<T>& matrix);
	Matrix<T> operator*(const T& value);
	Matrix<T> operator+(const Matrix<T>& matrix);
	
	T& operator[](unsigned int column);
};


#endif //LIGHTNN_MATRIX_H
