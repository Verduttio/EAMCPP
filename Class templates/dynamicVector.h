//
// Created by Bartek on 2022-04-02.
//

#ifndef LAB_05_DYNAMICVECTOR_H
#define LAB_05_DYNAMICVECTOR_H
#include "staticVector.h"
#include <algorithm>
#include <iostream>
#include "vectorException.h"

template<typename T>
class Vector<T, 0>  {
    int N;
    unique_ptr<T[]> array = nullptr;
private:
    Vector(unique_ptr<T[]> arr, int N) : array(move(arr)), N(N) {
        for(int i = 0; i < N; i++) {
            array[i] = arr[i];
        }
    }

public:
    typedef T value_type;

    explicit Vector(int N) : N(N), array(make_unique<T[]>(N)){
//        std::fill(array, array+N, 0);
        for(int i = 0; i < N; i++) {
            array[i] = 0;
        }
    }

    Vector(const Vector& vector_old) : N(vector_old.N), array(make_unique<T[]>(vector_old.N)){
//        std::copy(vector_old.array, vector_old.array+N, *array);
        for(int i = 0; i < N; i++) {
            array[i] = vector_old.array[i];
        }
    }

    Vector(std::initializer_list<T> data) : N(data.size()), array(make_unique<T[]>(data.size())){
//        std::copy(data.begin(), data.end(), array);
        for(int i = 0; i < data.size(); i++) {
            array[i] = *(data.begin()+i);
        }
    }

    // conversion
    template<typename S, int M>
    explicit Vector(const Vector<S, M>& v) {
        N = M;
        array = make_unique<T[]>(M);
        for(int i = 0; i < M; i++) {
            array[i] = v[i];
        }
    }

    int size() const{
        return N;
    }

    Vector operator+ (const Vector& v) {
        if(N != v.N) {
            throw VectorException("incompatible sizes in Vector::operator+");
        }

        Vector outVec = Vector(N);
        for(int i = 0; i < N; i++) {
            outVec.array[i] = array[i] + v.array[i];
        }
        return outVec;
    }

    template<int M>
    Vector<T, M> operator+ (const Vector<T, M>& v) {
        if(N != M) {
            throw VectorException("incompatible sizes in Vector::operator+");
        }

        Vector<T, M> outVec = Vector<T, M>();
        for(int i = 0; i < N; i++) {
            outVec[i] = array[i] + v[i];
        }
        return outVec;
    }

    T& operator[](int index) {
        return array[index];
    }

    T operator[](int index) const{
        return array[index];
    }

    void resize(int newSize) {
        auto modified = Vector(newSize);
        for(int i = 0; i < N; i++) {
            modified.array[i] = array[i];
        }
        N = newSize;
        auto mod = modified.array.release();
        array.reset(mod);
    }

    friend std::ostream & operator<< (std::ostream & out, const Vector & vector){
        for (int i = 0; i < vector.size(); i++) {
            out << vector.array[i] << " ";
        }
        return out;
    }

};



#endif //LAB_05_DYNAMICVECTOR_H
