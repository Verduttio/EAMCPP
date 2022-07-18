//
// Created by Bartek on 2022-04-30.
//

#ifndef LAB8_VECTORPOLICES_H
#define LAB8_VECTORPOLICES_H

class OutOfRangeException : public std::exception {
    [[nodiscard]] const char *what() const noexcept override {
        return "Index out of range";
    }
};


class SafePolicy {
protected:
    template <typename Type>
    void constructor(Type data, size_t N) const {
        for(int i = 0; i < N; i++) {
            data[i] = 0;
        }
    }

    template <typename Type>
    void constructor_initializerList(Type* data, size_t N, const std::initializer_list<Type> &list) const {
        if(list.size() <= N) {
            std::copy(list.begin(), list.end(), data);
        } else {
            std::cout<< "Exception" << std::endl;
//            throw OutOfRangeException();
        }
    }

    template<typename DataType, typename ReturnType>
    ReturnType get(DataType data, size_t index, size_t size) const {
        if(index < size && index >= 0) {
            return data[index];
        } else {
            std::cout<< "Exception" << std::endl;
//            throw OutOfRangeException();
        }
    }

    template<typename DataType, typename ValueType>
    void set(DataType&& data, size_t index, ValueType value, size_t size) {
        if(index < size && index >= 0) {
            data[index] = value;
        } else {
            std::cout<< "Exception" << std::endl;
            //throw OutOfRangeException();
        }
    }

};

class FastPolicy {
protected:
    template <typename Type>
    void constructor(Type data, size_t N) const {
    }

    template <typename Type>
    void constructor_initializerList(Type* data, size_t N, const std::initializer_list<Type> &list) const {
        std::copy(list.begin(), list.end(), data);
    }

    template<typename DataType, typename ReturnType>
    ReturnType get(DataType data, size_t index, size_t size) const {
        return data[index];
    }

    template<typename DataType, typename ValueType>
    void set(DataType&& data, size_t index, ValueType value, size_t size) {
        data[index] = value;
    }


};

class InitFastPolicy {
protected:
    template <typename Type>
    void constructor(Type data, size_t N) const {
        for(int i = 0; i < N; i++) {
            data[i] = 0;
        }
    }

    template <typename Type>
    void constructor_initializerList(Type* data, size_t N, const std::initializer_list<Type> &list) const {
        std::copy(list.begin(), list.end(), data);
    }

    template<typename DataType, typename ReturnType>
    ReturnType get(DataType data, size_t index, size_t size) const {
        return data[index];
    }

    template<typename DataType, typename ValueType>
    void set(DataType&& data, size_t index, ValueType value, size_t size) {
        data[index] = value;
    }
};

#endif //LAB8_VECTORPOLICES_H
