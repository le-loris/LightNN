//
// Created by loris on 30/09/2023.
//

#include "Matrix.h"


template<typename T> bool Matrix<T>::isEmpty() const{
	return (this->cursor.at(0) == this->cursor.at(1) == 0);
}

template<typename T> void Matrix<T>::enlarge(bool vertically, bool horizontally){
	vector<unsigned int> tempDim = this->dimensions;
	if(vertically)
		tempDim.at(0) += 10;

	if(horizontally)
		tempDim.at(1) += 10;

	T *temp = new T[tempDim.at(0) * tempDim.at(1)];
	for(int i = 0; i < this->dimensions.at(0) * this->dimensions.at(1); i++){
		temp[i] = this->values[i];
	}
	delete[] this->values;
	this->values = temp;	
}

template<typename T> Matrix<T>::Matrix(){
	this->dimensions = vector<unsigned int>(2);
	dimensions[0] = 10;
	dimensions[1] = 10;
	values = new T[dimensions[0] * dimensions[1]];
	this->cursor.at(0) = 0; this->cursor.at(1) = 0;
}

template<typename T> Matrix<T>::Matrix(vector<unsigned int> dimensions) {
	this->dimensions = dimensions;
	values = new T[dimensions[0] * dimensions[1]];
}

template<typename T> Matrix<T>::Matrix(unsigned int rows, unsigned int columns) {
	dimensions = vector<unsigned int>(2);
	dimensions[0] = rows;
	dimensions[1] = columns;
	values = new T[rows * columns];
}

template<typename T> Matrix<T>::Matrix(unsigned int rows, unsigned int columns, T* values) {
	dimensions = vector<unsigned int>(2);
	dimensions[0] = rows;
	dimensions[1] = columns;
	this->values = values;
}

template<typename T> Matrix<T>::Matrix(const Matrix& matrix) {
	dimensions = matrix.dimensions;
	values = new T[dimensions[0] * dimensions[1]];
	for (unsigned int i = 0; i < dimensions[0] * dimensions[1]; i++) {
		values[i] = matrix.values[i];
	}
}

template<typename T> Matrix<T>::~Matrix() {
	delete[] values;
}

template<typename T> T& Matrix<T>::at(unsigned int row, unsigned int column)
{
	if(row >= dimensions[0] || column >= dimensions[1]) {
		throw "Index out of bounds";
	}
	return this->values[row * dimensions[1] + column];
}

template<typename T> Matrix<T> Matrix<T>::transpose() const {
Matrix<T> result(dimensions[1], dimensions[0]);
	for (unsigned int i = 0; i < dimensions[0] * dimensions[1]; i++) {
		result(j, i) = this->at(i, j);
	}
	return result;
}

template<typename T> void Matrix<T>::addColumn(T* values){
	this->cursor.at(1)++;
	
	if(this->cursor.at(1) == this->dimensions.at(1))
		this->enlarge(false, true);
	if(values != nullptr)
		for(int i = 0; i < this->dimensions.at(0); i++)
			this->at(i, this->cursor.at(1)) = values[i];
	else
		for (int i = 0; i < this->dimensions.at(0); i++)
			this->at(i, this->cursor.at(1)) = 0;
}

template<typename T> void Matrix<T>::addRow(T* values){
	this->cursor.at(0)++;
	
	if(this->cursor.at(0) == this->dimensions.at(0))
		this->enlarge(true, false);
	
	if(values != nullptr)
		for(int i = 0; i < this->dimensions.at(1); i++)
			this->at(this->cursor.at(0), i) = values[i];
	else
		for (int i = 0; i < this->dimensions.at(1); i++)
			this->at(this->cursor.at(0), i) = 0;
}

template<typename T> T& Matrix<T>::operator[](unsigned int column){
	vector<unsigned int> result;
	for(int i = 0; i < dimensions[0]; i++){
		result.push_back(this->at(i, column));
	}
	return result;
}

template<typename T> Matrix<T> Matrix<T>::operator*(const Matrix<T>& matrix) {
	if (dimensions[1] != matrix.dimensions[0]) {
		throw "Matrix dimensions are not compatible";
	}
	Matrix<T> result(dimensions[0], matrix.dimensions[1]);
	for (unsigned int i = 0; i < dimensions[0]; i++) {
		for (unsigned int j = 0; j < matrix.dimensions[1]; j++) {
			result(i, j) = 0;
			for (unsigned int k = 0; k < dimensions[1]; k++) {
				result(i, j) += this->at(i, k) * matrix(k, j);
			}
		}
	}
	return result;
}

template<typename T> Matrix<T> Matrix<T>::operator*(const T& value) {
	Matrix<T> result(dimensions[0], dimensions[1]);
	for (unsigned int i = 0; i < dimensions[0] * dimensions[1]; i++) {
		result.values[i] = values[i] * value;
	}
	return result;
}

template<typename T> Matrix<T> Matrix<T>::operator+(const Matrix<T>& matrix) {
	if (dimensions[0] != matrix.dimensions[0] || dimensions[1] != matrix.dimensions[1]) {
		throw "Matrix dimensions are not compatible";
	}
	Matrix <T> result(dimensions[0], dimensions[1]);
	for (unsigned int i = 0; i < dimensions[0] * dimensions[1]; i++) {
		result.values[i] = values[i] + matrix.values[i];
	}
	return result;
}