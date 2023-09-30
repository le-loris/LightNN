//
// Created by loris on 30/09/2023.
//

#include "vector.h"

vector<T>(){
    this->max_length = 10;
    this->values = new T[this->max_length];
    for(i = 0; i < this->max_length; i++)
        this->values[i] = 0;
    
    this->cursor = 0;
}

~vector(){
    delete[] values;
}

void enlarge(){
    T *temp = new T[this->cursor+10];
    for(int i = 0; i < this->cursor; i++){
        temp[i] = this->at(i);
    }
    delete[] this->values;
    this->values = temp;
}

T at(unsigned int position){
    if((!isEmpty) && position < max_length)
        return values[position];
    
    else return T();
}

T back(){
    return this->at(cursor);
}

T front(){
    return this->at(0);
}

T pop_back(){
    if((!Empty)){
        float temp = this->back();
        values[cursor] = 0.f;
        cursor--;
        if(cursor == 0) isEmtpy = true;
        
        return temp;
    }
    else return 0.f;
}

T pop_front(){
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

unsigned int size(){
    return this->cursor;
}

void push_back(T value){
    if(this->cursor >= this->max_length-1)
        this->enlarge();
    
    this->set(++this->cursor) = value;
}

void push_front(T value){
    if(this->cursor >= this->max_length-1)
        this->enlarge();
    
    this->cursor++;

    for(int i = 1; value <= this->cursor; i++)
        this->set(this->at(i-1), i);
    
    this->set(value, 0);
}

int set(T value, unsigned int position){
    if(position < this->cursor) {
        values[position] = value;
        return position;
    }
    else return -1;
}

int insert(T value, unsigned  int position){
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
