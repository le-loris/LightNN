//
// Created by loris on 30/09/2023.
//

#ifndef LIGHTNN_MATRIX_H
#define LIGHTNN_MATRIX_H
#include "vector.h"
#include "define.h"

template <typename T>class Matrix {
private:
    T *values = nullptr;
    vector<unsigned int> dimensions;
	vector<unsigned int> cursor;
	bool isEmpty();
	void enlarge(bool horizontally = true, bool vertically = true);

public:
    Matrix();
	Matrix(vector<unsigned int> dimensions, T* values = nullptr);
	Matrix(unsigned int rows, unsigned int columns, T* values = nullptr);
	Matrix(const Matrix& other);
	Matrix(const Matrix&& other);
	static Matrix<T> identity(unsigned int size);
	static Matrix<T> random(unsigned int rows, unsigned int columns, T max, T min = T());
	static Matrix<T> fromVector(vector<T> values);
	
	Matrix<T> transpose();

	void clear();

	~Matrix();
	
	T& at(vector<unsigned int> position);
	T& transposedAt(vector<unsigned int> position);
	T& at(unsigned int row, unsigned int col);
	T& transposedAt(unsigned int row, unsigned int col);

	inline vector<unsigned int> size(){ return cursor;}
	inline unsigned int rows(){ return cursor.at(0); }
	inline unsigned int columns(){ return cursor.at(1); }
	
	void addRow(vector<T> row);
	void addColumn(vector<T> column);

	vector<T> getRow(unsigned int row);
	vector<T> getColumn(unsigned int column);

	Matrix<T>& operator+(const Matrix<T>& other);
	Matrix<T>& operator+=(const Matrix<T>& other);
	Matrix<T>& operator-(const Matrix<T>& other);
	Matrix<T>& operator*(const Matrix<T>& other);
	Matrix<T>& operator*(const T& scale);
};

template<typename T> vector<T>& operator*(const Matrix<T>& M, const vector<T>& V);
template<typename T> vector<T>& operator*(const vector<T>& V, const Matrix<T>& M);

template<typename T> Matrix<T>& operator&(const vector<T>& V1, const vector<T>& V2);


#endif //LIGHTNN_MATRIX_H
