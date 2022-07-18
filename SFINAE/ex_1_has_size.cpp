#include <iostream>
#include <vector>

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
template<typename T>
class hasSize<T, void_t<decltype(std::declval<T>().size())>> {
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

using namespace std;

int main() {
    cout << hasSize<int>::value << endl;
    cout << hasSize<vector<int>>::value << endl;
    cout << hasValueType<int>::value << endl;
    cout << hasValueType<vector<int>>::value << endl;

    return 0;
}




