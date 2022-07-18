//
// Created by Bartek on 2022-05-25.
//

#ifndef HOMEWORK_HAS_SIZE_VALUE_H
#define HOMEWORK_HAS_SIZE_VALUE_H

// void_t alias defined only for types
// that do not produce SFINAE error in its parameters
template <typename... Ts>
using void_t = void;

// Primary template
template<typename T, typename = void>
class hasSize {
public:
    static constexpr bool value = false;
};

// Partial specialization (only for types with size() method)
//https://stackoverflow.com/questions/1485983/calling-c-member-functions-via-a-function-pointer <- decltype(&T::size)
template<typename T>
class hasSize<T, void_t<decltype(&T::size)>> {
public:
    static constexpr bool value = true;
};

/// value_type
// Primary template
template<typename T, typename = void>
class hasValueType {
public:
    static constexpr bool value = false;
};

// Partial specialization (only for types with size() method)
template<typename T>
class hasValueType<T, void_t<typename T::value_type>> {
public:
    static constexpr bool value = true;
};

#endif //HOMEWORK_HAS_SIZE_VALUE_H
