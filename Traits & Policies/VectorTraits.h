//
// Created by Bartek on 2022-04-29.
//

#ifndef LAB8_VECTORTRAITS_H
#define LAB8_VECTORTRAITS_H

template<typename T>
class VectorTraits {
public:
    typedef const T & ParamType;
    static constexpr bool is_string {false};
    static T multiply(ParamType x, ParamType value) {
        return (x * value);
    }
};

template<>
class VectorTraits<std::basic_string<char>> {
public:
    typedef const int & ParamType;
    static constexpr bool is_string {true};

    static std::basic_string<char> multiply(ParamType x, const std::basic_string<char>& value) {
        std::basic_string<char> result;
        for(int i = 0; i < x; i++) {
            result += value;
        }
        return (result);
    }
};

#endif //LAB8_VECTORTRAITS_H
