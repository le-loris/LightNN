//
// Created by loris on 30/09/2023.
//

#ifndef LIGHTNN_VECTOR_H
#define LIGHTNN_VECTOR_H
#include<stdexcept>

template <class T>class vector {

private:
    T *values = nullptr;
    unsigned int max_length = 0;
    unsigned int cursor = 0;
    bool empty = true;
    void enlarge() {
        T* temp = new T[this->max_length + 10];
        for (unsigned int i = 0; i < this->max_length; i++) {
            temp[i] = this->values[i];
        }
        this->max_length += 10;
        delete[] this->values;
        this->values = temp;
    }

public:
    vector() : vector(10,nullptr) {
        this->cursor = 0;
        this->empty = true;
    };
    vector(unsigned int size, T* values = nullptr) {
        this->max_length = this->cursor = size;
        if (values == nullptr) {
            this->values = new T[this->max_length];
            for (unsigned int i = 0; i < this->max_length; i++)
                this->values[i] = T();
        }
        else
            this->values = values;
        this->empty = (size == 0);
    }
    vector(vector& vec) {
        this->max_length = this->cursor = vec.vector_length();

        this->values = new T[this->max_length];
        for (unsigned int i = 0; i < this->max_length; i++)
            this->values[i] = vec.at(i);
        
        this->empty = vec.isEmpty();
    }
    vector(vector&& vec)noexcept {
        this->max_length = this->cursor = vec.vector_length();

        this->values = new T[this->max_length];
        for (unsigned int i = 0; i < this->max_length; i++)
            this->at(i) = vec.at(i);
        this->empty = vec.isEmpty();
    }
    ~vector() {
        delete[] values;
    }

    bool isEmpty()const {return this->empty;}
    
    vector<T> copy()const {
        vector<T>copy(this->vector_length(), new T[this->vector_length()]);
        if(!this->isEmpty())
            for (unsigned int i = 0; i < this->vector_length(); i++)
                copy.at(i) = this->read(i);
        return copy;
    }
    T& at(unsigned int position) {
        if (isEmpty())
            throw std::out_of_range("Vector is empty");

        else if (position >= cursor)
            throw std::out_of_range("Index out of range");

        else return values[position];
    }
    T read(unsigned int position)const {
		if (isEmpty())
			throw std::out_of_range("Vector is empty");

		else if (position >= cursor)
			throw std::out_of_range("Index out of range");

		else return values[position];
    }
    T& back() {
        return this->at(cursor-1);
    }
    T& front() {
        return this->at(0);
    }
    T pop_back() { this->pop_index(this->cursor); }
    T pop_front() { this->pop_index(0); }
    T pop_index(unsigned int position) {
		if (isEmpty())
			throw std::out_of_range("Vector is empty");
		else if (position > cursor)
			throw std::out_of_range("Index out of range");
		else {
			float temp = this->at(position);
			for (int i = position; i < this->max_length - 1; i++) {
				values[i] = values[i + 1];
			}
			cursor--;
			if (cursor == 0) this->isEmpty() = true;
		}
	}

    unsigned int vector_length() const{return this->cursor;}
    void push_back(T value) { this->push_index(value, this->cursor); };
    void push_front(T value) { this->push_index(value, 0); };
    int push_index(T value, unsigned int position) {
        if (this->cursor - 1 >= this->max_length)
            enlarge();

        this->empty = false;
        this->cursor++;
        if(this->cursor > 1)
            for (unsigned int i = position + 1; i <= this->cursor; i++)
                this->at(i - 1) = this->values[i];

        this->at(position) = value;
        return position;
    }

    T norm_sq() {
        T norm = 0;
        for (unsigned int i = 0; i < this->vector_length(); i++)
            norm += this->at(i) * this->at(i);

        return norm;
    }
    void clear() {
        if (this->isEmpty())
            return;

        for (unsigned int i = 0; i < this->max_length; i++)
            this->at(i) = T(0);
        this->cursor = 0;
    }


    vector<T> operator*(const vector<T> &vec) {
        if (this->vector_length() != vec.vector_length())
            throw std::invalid_argument("Vectors must have the same size for dot product");

        vector<T> temp(this->vector_length(), nullptr);
        for (unsigned int i = 0; i < this->vector_length(); i++)
            temp.at(i) = this->at(i) * vec.read(i);

        return temp;
    }
    vector<T> operator+(const vector<T> &vec) {
        if (this->vector_length() != vec.vector_length())
            throw std::invalid_argument("Vectors must have the same size for addition");

        vector<T> temp(this->vector_length(), nullptr);
        for (unsigned int i = 0; i < this->vector_length(); i++)
            temp.at(i) = this->read(i) + vec.read(i);

        return temp;
    }
    vector<T> operator-(const vector<T> &vec) {
        if (this->vector_length() != vec.vector_length())
            throw std::invalid_argument("Vectors must have the same size for subtraction");

        vector<T> temp(this->vector_length(), nullptr);
        for (unsigned int i = 0; i < this->vector_length(); i++)
            temp.at(i) = this->at(i) - vec.read(i);

        return temp;
    }
    vector<T> operator*(const T& scalar) {
        vector<T> temp(this->length(), nullptr);
        for (int i = 0; i < this->length(); i++)
            temp.at(i) = this->at(i) * scalar;

        return temp;
    }
    vector<T> operator/(const T& scalar) {
        vector<T> temp(this->length(), nullptr);
        for (int i = 0; i < this->length(); i++)
            temp.at(i) = this->at(i) / scalar;

        return temp;
    }
    vector<T>& operator=(const vector<T> &vec) {
        delete[] this->values;
        this->max_length = this->cursor = vec.vector_length();
        this->values = new T[this->max_length];
        if(!vec.isEmpty())
            for (unsigned int i = 0; i < this->max_length; i++)
                this->values[i] = vec.read(i);
        this->empty = vec.isEmpty();
        return *this;
    }
    T& operator[](unsigned int position) {return this->at(position);}
    
};


#endif //LIGHTNN_VECTOR_H
