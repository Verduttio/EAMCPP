//
// Created by Bartek on 2022-04-01.
//

#ifndef LAB_05_STATICVECTOR_H
#define LAB_05_STATICVECTOR_H

#include <algorithm>

template<typename T, int N>
class Vector;

template<typename T, int N>
std::ostream& operator<<(std::ostream& out, const Vector<T, N>&);



template <typename T, int N>
class Vector {
    T array [N];

private:
    Vector(T arr []) {
        for(int i = 0; i < N; i++) {
            array[i] = arr[i];
        }
    }
public:
    //using value_type = T;
    typedef T value_type;

    Vector() {
        for(auto el : array) {
            el = 0;
        }
    }

//    Vector(const Vector& vector_old) = default;
    Vector(const Vector& vector_old) {
        std::copy(vector_old.array, vector_old.array+N, array);
    }


    Vector(std::initializer_list<T> data) {
        std::copy(data.begin(), data.end(), array);
    }

    // conversion
    template<typename S, int M>
    explicit Vector(const Vector<S, M>& v) {
        for(int i = 0; i < M; i++) {
            array[i] = v[i];
        }
    }

    template<typename S>
    explicit Vector(const Vector<S, 0>& v) {
        for(int i = 0; i < N; i++) {
            array[i] = v[i];
        }
    }

    int size() const{
        return N;
    }

    Vector operator+ (const Vector& v) {
        T outArray[N];
        for(int i = 0; i < N; i++) {
            outArray[i] = array[i] + v.array[i];
        }
        return Vector(outArray);
    }

    Vector<T, N> operator+ (const Vector<T, 0>& v) {
        T outArray[N];
        for(int i = 0; i < N; i++) {
            outArray[i] = array[i] + v[i];
        }
        return Vector(outArray);
    }

    T& operator[](int index) {
        return array[index];
    }

    T operator[](int index) const{
        return array[index];
    }



    friend std::ostream & operator<< (std::ostream & out, const Vector & vector){
        for (int i = 0; i < vector.size(); i++) {
            out << vector.array[i] << " ";
        }
        return out;
    }
};

#endif //LAB_05_STATICVECTOR_H
