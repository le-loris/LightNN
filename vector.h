//
// Created by loris on 30/09/2023.
//

#ifndef LIGHTNN_VECTOR_H
#define LIGHTNN_VECTOR_H


class vector<T> {

private:
    T *values = nullptr;
    unsigned int max_length = 0;
    unsigned int cursor = 0;
    bool isEmpty = true;
    void enlarge();

public:
    vector();
    ~vector();
    T at(unsigned int position);
    T back();
    T front();
    T pop_back();
    T pop_front();

    unsigned int size();
    void push_back(T value);
    void push_front(T value);
    int set(T value, unsigned int position);
    int insert(T value, unsigned int position);

};


#endif //LIGHTNN_VECTOR_H
