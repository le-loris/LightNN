//
// Created by loris on 30/09/2023.
//

#include "Matrix.h"

template<typename T> bool Matrix<T>::isEmpty(){
	if (cursor.size() != 2)
		return true;

	if(cursor.at(0) == 0 || cursor.at(1) == 0)
		return true;

	return false;
}

template<typename T>void Matrix<T>::enlarge(bool horizontally, bool vertically){
	if(vertically)
		this->dimensions.at(0) += 10;
	if(horizontally)
		this->dimensions.at(1) += 10;

	T *temp = new T[this->dimensions.at(0) * this->dimensions.at(1)];
	for (int i = 0; i < this->dimensions.at(0) * this->dimensions.at(1); i++)
		temp[i] = this->values[i];
	delete[] this->values;
	this->values = temp;
}

template<typename T> Matrix<T>::Matrix(){
	this->dimensions = vector<unsigned int>(2);
	this->dimensions.push_back(10);
	this->dimensions.push_back(10);
	this->values = new T[this->dimensions.at(0) * this->dimensions.at(1)];
	for (int i = 0; i < this->dimensions.at(0) * this->dimensions.at(1); i++)
		this->values[i] = T();

	this->cursor = vector<unsigned int>(2);
}

template<typename T> Matrix<T>::Matrix(vector<unsigned int> dimensions, T* values){
	this->dimensions = this->cursor = dimensions;
	
	if (values == nullptr) {
		this->values = new T[this->dimensions.at(0) * this->dimensions.at(1)];
		for (int i = 0; i < this->dimensions.at(0) * this->dimensions.at(1); i++)
			this->values[i] = T();
	}
	else
		this->values = values;	
}

template<typename T>Matrix<T>::Matrix(unsigned int rows, unsigned int columns, T* values)
{
	vector<unsigned int> temp(2);
	temp.push_back(rows);
	temp.push_back(columns);
	Matrix(temp, values);
}

template<typename T> Matrix<T>::Matrix(const Matrix& other) {
	this->dimensions = this->cursor = other.size();
	this->values = new T[this->dimensions.at(0) * this->dimensions.at(1)];
	for (int i = 0; i < this->dimensions.at(0) * this->dimensions.at(1); i++)
		this->values[i] = other.values[i];
}

template<typename T> Matrix<T> Matrix<T>::identity(unsigned int size){
	Matrix<T> temp(size, size, new T[size * size]);
	for (int i = 0; i < size; i++)
		temp.set(T(1), vector<unsigned int>(2, i));
	return temp;
}

template<typename T> Matrix<T> Matrix<T>::random(unsigned int rows, unsigned int columns, T max, T min){
	Matrix<T> temp(rows, columns, new T[rows * columns]);
	for (int i = 0; i < rows * columns; i++)
		temp.values[i] = T((rand() % (max - min + 1)) + min);
	return temp;
}

template<typename T> Matrix<T> Matrix<T>::fromVector(vector<T> values){
	Matrix<T> temp(1, values.size(), values);
}

template<typename T> Matrix<T> Matrix<T>::transpose() {
	Matrix<T> temp(this->dimensions.at(1), this->dimensions.at(0), new T[this->dimensions.at(0) * this->dimensions.at(1)]);
	for (int i = 0; i < this->dimensions.at(0); i++)
		for (int j = 0; j < this->dimensions.at(1); j++)
			temp.set(this->at(i, j), j, i);
	return temp;

}

template<typename T> Matrix<T>::~Matrix(){
	delete[] this->values;
}

template<typename T> T& Matrix<T>::at(vector<unsigned int> position) {
	if (position.size() != 2)
		throw "Invalid position size for Matrix::at()";

	else return this->at(position.at(0), position.at(1));	return this->at(position.at(0), position.at(1));
}

template<typename T> T& Matrix<T>::transposedAt(vector<unsigned int> position) {
	if (position.size() != 2)
		throw "Invalid position size for Matrix::at()";

	else return this->transposedAt(position.at(0), position.at(1));
}

template<typename T> T& Matrix<T>::at(unsigned int row, unsigned int col) {
	if (row >= this->cursor.at(0) || col >= this->cursor.at(1))
		throw "Invalid position for Matrix::at()";

	else return this->values[row * this->dimensions.at(1) + col];
}

template<typename T> T& Matrix<T>::transposedAt(unsigned int row, unsigned int col){
	return this->at(col, row);
}

template<typename T> void Matrix<T>::addRow(vector<T> row){
	if (row.size() != this->dimensions.at(1))
		throw "Invalid row size";

	if (this->cursor.at(0) == this->dimensions.at(0))
		this->enlarge(true, false);

	for (int i = 0; i < this->dimensions.at(1); i++)
		this->at(this->cursor.at(0), i) = row.at(i);

	this->cursor.at(0)++;
}

template<typename T> void Matrix<T>::addColumn(vector<T> column){
	if (column.size() != this->dimensions.at(0))
		throw "Invalid column size for Matrix::addColumn";

	if (this->cursor.at(1) == this->dimensions.at(1))
		this->enlarge(false, true);

	for (int i = 0; i < this->dimensions.at(0); i++)
		this->at(i, this->cursor.at(1)) = column.at(i);

	this->cursor.at(1)++;
}

template<typename T> vector<T> Matrix<T>::getRow(unsigned int row){
	if (row >= this->dimensions.at(0))
		throw "Invalid row for Matrix::getRow()";

	vector<T> temp(this->dimensions.at(1));
	for (int i = 0; i < this->dimensions.at(1); i++)
		temp.at(i) = this->at(row, i);
	return temp;
}

template<typename T> vector<T> Matrix<T>::getColumn(unsigned int column){
	if (column >= this->dimensions.at(1))
		throw "Invalid column for Matrix::getColumn()";

	vector<T> temp(this->dimensions.at(0));
	for (int i = 0; i < this->dimensions.at(0); i++)
		temp.at(i) = this->at(i, column);
	return temp;
}

template<typename T> Matrix<T> Matrix<T>::operator+(const Matrix<T>& other){
	if (this->dimensions != other.dimensions)
		throw "Invalid dimensions size for Matrix addition";

	Matrix<T> temp(this->dimensions, new T[this->dimensions.at(0) * this->dimensions.at(1)]);
	for (int i = 0; i < this->dimensions.at(0) * this->dimensions.at(1); i++)
		temp.values[i] = this->values[i] + other.values[i];
	return temp;
}

template<typename T> Matrix<T> Matrix<T>::operator-(const Matrix<T>& other){
	if (this->dimensions != other.dimensions)
		throw "Invalid dimensions for Matrix substraction";

	Matrix<T> temp(this->dimensions, new T[this->dimensions.at(0) * this->dimensions.at(1)]);
	for (int i = 0; i < this->dimensions.at(0) * this->dimensions.at(1); i++)
		temp.values[i] = this->values[i] - other.values[i];
	return temp;
}

template<typename T> Matrix<T> Matrix<T>::operator*(const Matrix<T>& other){
	if (this->dimensions.at(1) != other.dimensions.at(0))
		throw "Invalid dimensions for Matrix product";

	Matrix<T> temp(this->dimensions.at(0), other.dimensions.at(1), new T[this->dimensions.at(0) * other.dimensions.at(1)]);
	for (int i = 0; i < this->dimensions.at(0); i++)
		for (int j = 0; j < other.dimensions.at(1); j++)
			for (int k = 0; k < this->dimensions.at(1); k++)
				temp.at(i, j) += this->at(i, k) * other.at(k, j);
	return temp;
}

template<typename T> Matrix<T> Matrix<T>::operator*(const T& scale){
	Matrix<T> temp(this->dimensions, new T[this->dimensions.at(0) * this->dimensions.at(1)]);
	for (int i = 0; i < this->dimensions.at(0) * this->dimensions.at(1); i++)
		temp.values[i] = this->values[i] * scale;
	return temp;
}

template<typename T> vector<T> operator*(const Matrix<T>& M, const vector<T>& V){
	if (M->dimensions.at(0) != V.size())
		throw "Invalid dimensions for Matrix product";

	vector<T> temp(M->dimensions.at(1));
	for (int i = 0; i < M->dimensions.at(1); i++)
		for (int j = 0; j < M->dimensions.at(0); j++)
			temp.at(i) += M->at(j, i) * V.at(j);
	return temp;
}

template<typename T> vector<T> operator*(const vector<T>& V, const Matrix<T>& M) {
	if (M->dimensions.at(1) != V.size())
		throw "Invalid dimensions for Matrix product";

	vector<T> temp(M->dimensions.at(0));
	for (int i = 0; i < M->dimensions.at(0); i++)
		for (int j = 0; j < M->dimensions.at(1); j++)
			temp.at(i) += M->at(i, j) * V.at(j);
	return temp;
}
