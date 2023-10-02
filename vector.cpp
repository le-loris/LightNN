//
// Created by loris on 30/09/2023.
//

#include "vector.h"

template<typename T> vector<T>::vector()
{
    vector(10, nullptr);
    this->cursor = 0;
}

template<typename T> vector<T>::vector(unsigned int size, T* values){
    this->max_length = this->cursor = size;
    if(values == nullptr){
        this->values = new T[this->max_length];
        for (i = 0; i < this->max_length; i++)
            this->values[i] = T();
    }
    else
        this->values = values;   
}

template<typename T> vector<T>::vector(vector& vec){
    this->max_length = this->cursor = vec.size();

    this->values = new T[this->max_length];
    for(i = 0; i < this->max_length; i++)
		this->values[i] = vec.at(i);
}

template <typename T> vector<T>::~vector(){
    delete[] values;
}

template <typename T> void vector<T>::enlarge(){
    T *temp = new T[this->cursor+10];
    for(int i = 0; i < this->cursor; i++){
        temp[i] = this->at(i);
    }
    delete[] this->values;
    this->values = temp;
}

template <typename T> T& vector<T>::at(unsigned int position){
    if(isEmpty)
        throw std::out_of_range("Vector is empty");

    else if (position >= cursor)
        throw std::out_of_range("Index out of range");

    else return values[position];
}

template <typename T> T vector<T>::back(){
    return this->at(cursor);
}

template <typename T> T vector<T>::front(){
    return this->at(0);
}

template <typename T> T vector<T>::pop_back(){
    if(isEmpty)
		throw std::out_of_range("Vector is empty");

	else{
        float temp = this->back();
        values[cursor] = T();
        cursor--;
        if(cursor == 0) isEmtpy = true;
        
        return temp;
    }
}

template <typename T> T vector<T>::pop_front(){
    if(isEmpty)
        throw std::out_of_range("Vector is empty");
    else{
        float temp = this->front();
        for(int i = 0; i < this->max_length-1; i++){
            values[i] = values[i+1];
        }
        cursor--;
        if(cursor == 0) isEmtpy = true;
    }
}

template <typename T> unsigned int vector<T>::size(){
    return this->cursor;
}

template <typename T> void vector<T>::push_back(T value){
    if(this->cursor >= this->max_length-1)
        this->enlarge();
    
    this->at(++this->cursor) = value;
}

template <typename T> void vector<T>::push_front(T value){
    if(this->cursor >= this->max_length-1)
        this->enlarge();
    
    this->cursor++;

    for(int i = 1; value <= this->cursor; i++)
        this->set(this->at(i-1), i);
    
    this->at(0) = value;
}

template <typename T> int vector<T>::insert(T value, unsigned  int position){
   if(position > this->cursor+1)
       throw std::out_of_range("Index out of range, use vector::push_back() istead");
   else{
        if(this->cursor >= this->max_length-1)
            enlarge();

        this->cursor++;
        for (int i = position + 1; i <= this->cursor)
            this->set(this->at(i - 1), i)

        this->set(value, position);
        return position;
    }
}
