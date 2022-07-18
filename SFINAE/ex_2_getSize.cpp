#include <iostream>
#include <vector>
#include "has_size_value.h"

using namespace std;

namespace v1 {
    template<typename T>
    std::enable_if_t<hasSize<T>::value && hasValueType<T>::value, std::size_t>
    getSize(const T &x) {
        return x.size() * sizeof(typename T::value_type);
    }

    template<typename T>
    std::enable_if_t<!(hasSize<T>::value && hasValueType<T>::value), std::size_t>
    getSize(const T &x) {
        return sizeof(x);
    }
}

namespace v2{
    template<typename T>
    std::size_t getSize(const T& x) {
        if constexpr(hasSize<T>::value && hasValueType<T>::value) {
            return x.size() * sizeof(typename T::value_type);
        } else {
            return sizeof(x);
        }
    }
}


int main() {
    std::vector<int> v{1,2,3,4,5};
    cout << v1::getSize(5) << endl;
    cout << v1::getSize(v) << endl;
    cout << v2::getSize(5) << endl;
    cout << v2::getSize(v) << endl;
    return 0;
}
