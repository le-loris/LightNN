//
// Created by loris on 30/09/2023.
//

#include "vector.h"

template <typename T> vector<T>::vector(){
    this->max_length = 10;
    this->values = new T[this->max_length];
    for(i = 0; i < this->max_length; i++)
        this->values[i] = 0;
    
    this->cursor = 0;
}

template<typename T>
vector<T>::vector(unsigned int size)
{
    this->max_length = size;
    this->values = new T[this->max_length];
    for (i = 0; i < this->max_length; i++)
        this->values[i] = 0;

    this->cursor = 0;
}

template<typename T>
vector<T>::vector(const vector& vector)
{
    this->max_length = vector.size();
    this->values = new T[this->max_length];
    for (i = 0; i < this->max_length; i++)
        this->values[i] = vector[i];

    this->cursor = vector.size();
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
    if((!isEmpty) && position < max_length)
        return values[position];
    
    else return T();
}

template <typename T> T vector<T>::back(){
    return this->at(cursor);
}

template <typename T> T vector<T>::front(){
    return this->at(0);
}

template <typename T> T vector<T>::pop_back(){
    if((!Empty)){
        float temp = this->back();
        values[cursor] = 0.f;
        cursor--;
        if(cursor == 0) isEmtpy = true;
        
        return temp;
    }
    else return 0.f;
}

template <typename T> T vector<T>::pop_front(){
    if((!Empty)){
        float temp = this->front();
        for(int i = 0; i < this->max_length-1; i++){
            values[i] = values[i+1];
        }
        cursor--;
        if(cursor == 0) isEmtpy = true;
    }
    else return 0.f;
}

template <typename T> unsigned int vector<T>::size(){
    return this->cursor;
}

template <typename T> void vector<T>::push_back(T value){
    this->cursor++;
    if(this->cursor == this->max_length)
        this->enlarge();
    
    this->at(this->cursor) = value;
}

template <typename T> void vector<T>::push_front(T value){
    this->cursor++;

    if(this->cursor == this->max_length)
        this->enlarge();
    
    for(int i = 1; value <= this->cursor; i++)
        this->set(this->at(i-1), i);
    
    this->at(0) = value;
}

template <typename T> int vector<T>::set(T value, unsigned int position){
    if(position < this->cursor) {
        values[position] = value;
        return position;
    }
    else return -1;
}

template <typename T> int vector<T>::insert(T value, unsigned  int position){
    if(position <= this->cursor+1) {
        if(this->cursor >= this->max_length-1)
            enlarge();


        this->cursor++;
        for (int i = position + 1; i <= this->cursor)
            this->set(this->at(i - 1), i)

        this->set(value, position);
        return position;
    }
    else return -1;
}

template<typename T> T& vector<T>::operator[](unsigned int position){
    return this->at(position);
}
