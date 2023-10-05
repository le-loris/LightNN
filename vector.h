//
// Created by loris on 30/09/2023.
//

#ifndef LIGHTNN_VECTOR_H
#define LIGHTNN_VECTOR_H
#include<stdexcept>

template <typename T> class vector {

template <typename T>class vector {

private:
    T *values = nullptr;
    unsigned int max_length = 0;
    unsigned int cursor = 0;
    bool isEmpty = true;
    void enlarge();

public:
    vector();
    vector(unsigned int size, T* values = nullptr);
    vector(vector& vec);
    vector(vector&& vec);
    ~vector();
    T& at(unsigned int position);
    T& back();
    T& front();
    T pop_back();
    T pop_front();

    unsigned int size();
    void push_back(T value);
    void push_front(T value);
    int insert(T value, unsigned int position);

    T norm_sq();
    void clear();


    vector<T>& operator*(const vector<T> &vec);
    vector<T>& operator+(const vector<T> &vec);
    vector<T>& operator-(const vector<T> &vec);
    vector<T>& operator*(const T& scalar);
    vector<T>& operator/(const T& scalar);
    vector<T>& operator=(const vector<T> &vec);
    vector<T>& operator=(vector<T> &&vec);
    T& operator[](unsigned int position);
    bool operator==(const vector<T> &vec);
    bool operator!=(const vector<T> &vec);

};


#endif //LIGHTNN_VECTOR_H
