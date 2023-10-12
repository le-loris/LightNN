//
// Created by loris on 30/09/2023.
//

#ifndef LIGHTNN_MATRIX_H
#define LIGHTNN_MATRIX_H
#include "vector.h"
#include "define.h"

template <class T>class Matrix {
private:
    T *values = nullptr;
    vector<unsigned int> dimensions;
	vector<unsigned int> cursor;
	void enlarge(bool horizontally = true, bool vertically = true) {
		if (vertically)
			this->dimensions.at(0) += 10;
		if (horizontally)
			this->dimensions.at(1) += 10;

		T* temp = new T[this->dimensions.at(0) * this->dimensions.at(1)];
		for (int i = 0; i < this->dimensions.at(0) * this->dimensions.at(1); i++)
			temp[i] = this->values[i];
		delete[] this->values;
		this->values = temp;
	}

public:
	Matrix() {
		this->dimensions = vector<unsigned int>();
		this->dimensions.push_back(10); this->dimensions.push_back(10);
		this->cursor = vector<unsigned int>();
		this->cursor.push_back(10); this->cursor.push_back(10);
		this->values = new T[this->dimensions.at(0) * this->dimensions.at(1)];
		for (unsigned int i = 0; i < this->dimensions.at(0); i++)
			for (unsigned int j = 0; j < this->dimensions.at(1); j++)
				this->at(i, j) = T();
	}
	Matrix(vector<unsigned int> dimensions, T* values = nullptr) : Matrix(dimensions.at(0), dimensions.at(1), values) {}
	Matrix(unsigned int rows, unsigned int columns, T* values = nullptr)
	{
		this->dimensions.push_back(rows);
		this->dimensions.push_back(columns);
		this->cursor = this->dimensions;

		if (values == nullptr) {
			this->values = new T[this->dimensions.at(0) * this->dimensions.at(1)];
			for (unsigned int i = 0; i < this->dimensions.at(0); i++)
				for(unsigned int j = 0; j < this->dimensions.at(1); j++)
					this->at(i, j) = T();
		}
		else
			this->values = values;
	}
	Matrix(const Matrix& other) {
		this->dimensions = this->cursor = other.size();
		this->values = new T[this->dimensions.at(0) * this->dimensions.at(1)];
		for (unsigned int i = 0; i < this->dimensions.at(0); i++)
			for(unsigned int j = 0; j < this->dimensions.at(1); j++)
				this->at(i, j) = other.values[i];
	}
	Matrix(const Matrix&& other) noexcept{
		this->dimensions = this->cursor = other.size();
		this->values = new T[this->dimensions.at(0) * this->dimensions.at(1)];
		for (unsigned int i = 0; i < this->dimensions.at(0); i++)
			for(unsigned int j = 0; j < this->dimensions.at(1); j++)
				this->at(i, j) = other.read(i, j);
	}
	static Matrix<T> identity(unsigned int size) {
		Matrix<T> temp(size, size, new T[size * size]);
		for (int i = 0; i < size; i++)
			temp.set(T(1), vector<unsigned int>(2, i));
		return temp;
	}
	static Matrix<T> random(unsigned int rows, unsigned int columns, T max, T min = T()) {
		Matrix<T> temp(rows, columns, new T[rows * columns]);
		for (int i = 0; i < rows * columns; i++)
			temp.values[i] = T((rand() % (max - min + 1)) + min);
		return temp;
	}
	static Matrix<T> fromVector(vector<T> values) {
		Matrix<T> temp(1, values.vector_length(), values);
	}
	
	Matrix<T> transpose() {
		Matrix<T> temp(this->dimensions.at(1), this->dimensions.at(0), new T[this->dimensions.at(0) * this->dimensions.at(1)]);
		for (unsigned int i = 0; i < this->dimensions.at(0); i++)
			for (unsigned int j = 0; j < this->dimensions.at(1); j++)
				this->at(i, j) = temp.at(j, i);
		return temp;

	}

	void clear() {
		for (unsigned int i = 0; i < this->dimensions.at(0) * this->dimensions.at(1); i++)
			this->values[i] = T();

		this->cursor = vector<unsigned int>(2);
	}

	~Matrix() {
		delete[] this->values;
	}
	
	T read(unsigned int row, unsigned int col)const {
		if (row >= this->dimensions.read(0) || col >= this->dimensions.read(1))
			throw "Invalid position for Matrix::read()";

		else return this->values[row * this->dimensions.read(1) + col];
	}
	T& at(vector<unsigned int> position) {
		if (position.vector_length() != 2)
			throw "Invalid position size for Matrix::at()";

		else return this->at(position.at(0), position.at(1));	return this->at(position.at(0), position.at(1));
	}
	T& transposedAt(vector<unsigned int> position) {
		if (position.vector_length() != 2)
			throw "Invalid position size for Matrix::at()";

		else return this->transposedAt(position.at(0), position.at(1));
	}
	T& at(unsigned int row, unsigned int col) {
		if (row >= this->cursor.read(0) || col >= this->cursor.read(1))
			throw "Invalid position for Matrix::at()";

		else return this->values[row * this->dimensions.at(1) + col];
	}
	T& transposedAt(unsigned int row, unsigned int col) {
		return this->at(col, row);
	}

	bool isEmpty() const{
		if (cursor.vector_length() != 2)
			return true;

		if (cursor.read(0) == 0 || cursor.read(1) == 0)
			return true;

		return false;
	}

	vector<unsigned int> size() const{ return this->cursor.copy();}
	unsigned int rows()const{ return cursor.read(0); }
	unsigned int columns()const{ return cursor.read(1); }
	
	void addRow(vector<T> row) {
		if (row.vector_length() != this->dimensions.at(1))
			throw "Invalid row size";

		if (this->cursor.at(0) == this->dimensions.at(0))
			this->enlarge(true, false);

		for (int i = 0; i < this->dimensions.at(1); i++)
			this->at(this->cursor.at(0), i) = row.at(i);

		this->cursor.at(0)++;
	}
	void addColumn(vector<T> column) {
		if (column.vector_length() != this->dimensions.at(0))
			throw "Invalid column size for Matrix::addColumn";

		if (this->cursor.at(1) == this->dimensions.at(1))
			this->enlarge(false, true);

		for (int i = 0; i < this->dimensions.at(0); i++)
			this->at(i, this->cursor.at(1)) = column.at(i);

		this->cursor.at(1)++;
	}

	vector<T> getRow(unsigned int row) {
		if (row >= this->dimensions.at(0))
			throw "Invalid row for Matrix::getRow()";

		vector<T> temp(this->dimensions.at(1));
		for (int i = 0; i < this->dimensions.at(1); i++)
			temp.at(i) = this->at(row, i);
		return temp;
	}
	vector<T> getColumn(unsigned int column) {
		if (column >= this->dimensions.at(1))
			throw "Invalid column for Matrix::getColumn()";

		vector<T> temp(this->dimensions.at(0));
		for (int i = 0; i < this->dimensions.at(0); i++)
			temp.at(i) = this->at(i, column);
		return temp;
	}

	Matrix<T>& operator+(const Matrix<T>& other) {
		if (this->dimensions != other.dimensions)
			throw "Invalid dimensions size for Matrix addition";

		Matrix<T> temp(this->dimensions, new T[this->dimensions.at(0) * this->dimensions.at(1)]);
		for (int i = 0; i < this->dimensions.at(0) * this->dimensions.at(1); i++)
			temp.values[i] = this->values[i] + other.values[i];
		return temp;
	}
	Matrix<T>& operator+=(const Matrix<T>& other)
	{
		if ((this->rows() != other.rows()) || (this->columns() != other.columns()))
			throw "Invalid dimensions size for Matrix addition";

		for (unsigned int i = 0; i < this->dimensions.at(0) * this->dimensions.at(1); i++)
			this->values[i] += other.values[i];
		return *this;
	}
	Matrix<T>& operator-(const Matrix<T>& other) {
		if (this->dimensions != other.dimensions)
			throw "Invalid dimensions for Matrix substraction";

		Matrix<T> temp(this->dimensions, new T[this->dimensions.at(0) * this->dimensions.at(1)]);
		for (int i = 0; i < this->dimensions.at(0) * this->dimensions.at(1); i++)
			temp.values[i] = this->values[i] - other.values[i];
		return temp;
	}
	Matrix<T>& operator*(const Matrix<T>& other) {
		if (this->dimensions.at(1) != other.dimensions.at(0))
			throw "Invalid dimensions for Matrix product";

		Matrix<T> temp(this->dimensions.at(0), other.dimensions.at(1), new T[this->dimensions.at(0) * other.dimensions.at(1)]);
		for (int i = 0; i < this->dimensions.at(0); i++)
			for (int j = 0; j < other.dimensions.at(1); j++)
				for (int k = 0; k < this->dimensions.at(1); k++)
					temp.at(i, j) += this->at(i, k) * other.at(k, j);
		return temp;
	}
	Matrix<T> operator*(const T& scale) {
		Matrix<T> temp(this->dimensions, new T[this->dimensions.at(0) * this->dimensions.at(1)]);
		for (unsigned int i = 0; i < this->dimensions.at(0) * this->dimensions.at(1); i++)
			temp.values[i] = this->values[i] * scale;
		return temp;
	}
	Matrix<T>& operator=(const Matrix<T>& other) {
		delete[] this->values;
		this->dimensions = this->cursor = other.size();
		this->values = new T[this->dimensions.at(0) * this->dimensions.at(1)];
		if(other.isEmpty())
			for (unsigned int i = 0; i < this->dimensions.at(0); i++)
				for(unsigned int j = 0; j < this->dimensions.at(1); j++)
					this->at(i, j) = other.read(i, j);
		return *this;
	}
	vector<T>& operator[](unsigned int column){ return this->getColumn(column);	}

	friend std::ostream& operator<<(std::ostream& flux, Matrix<T>& M) {
		char* buf = new char[10];
		for (unsigned int i = 0; i < M.rows(); i++) {
			for (unsigned int j = 0; j < M.columns(); j++) {
				sprintf(buf, "%.5f   ", M.at(i, j));
				flux << buf;
			}
			flux << std::endl;
		}
		return flux;
	}
	
	
};

template<class T> vector<T> operator*(const vector<T>& V, const Matrix<T>& M) {
	if (M.columns() != V.vector_length())
		throw "Invalid dimensions for Matrix product";

	vector<T> temp(M.rows());
	for (int i = 0; i < M.rows(); i++)
		for (int j = 0; j < M.columns(); j++)
			temp.at(i) += M.read(i, j) * V.read(j);
	return temp;
}

template<typename T> vector<T> operator*(const Matrix<T>& M, const vector<T>& V) {
	if (M.rows() != V.vector_length()) 
		throw std::out_of_range("Invalid dimensions for Matrix product");
	
	vector<T> temp(M.columns());
	for (unsigned int i = 0; i < M.columns(); i++)
		for (unsigned int j = 0; j < M.rows(); j++)
			temp.at(i) += M.read(j, i) * V.read(j);
	return temp;
}

template<class T> Matrix<T> operator&(const vector<T>& V1, const vector<T>& V2) {
	Matrix<T> temp(V1.vector_length(), V2.vector_length(), new T[V1.vector_length() * V2.vector_length()]);
	for (unsigned int i = 0; i < V1.vector_length(); i++)
		for (unsigned int j = 0; j < V2.vector_length(); j++)
			temp.at(i, j) = V1.read(i) * V2.read(j);

	return temp;
}

#endif //LIGHTNN_MATRIX_H