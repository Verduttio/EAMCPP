#include <iostream>
#include <limits>
using  namespace std;
/**
 * Outputs information about numerical type T:
 * (un)signed, (not) integer, min & max values
*/
template <typename T>
void info(T x){
    string signed_info = is_signed<T>::value ? "signed" : "unsigned";
    string integer_info = is_integral<T>::value ? "integer" : "not integer";
    auto min_info = numeric_limits<T>::min();
    auto max_info = numeric_limits<T>::max();

    cout << signed_info + ", " + integer_info + ", min : " << min_info << " max : " << max_info << endl;
}

int main() {
    info(1);
    info(2.0f);
    info(3U);
    return 0;
}
/**
 * Expected output:
    signed,  integer, min : -2147483648 max : 2147483647
    signed, not integer, min : 1.17549e-38 max : 3.40282e+38
    unsigned,  integer, min : 0 max : 4294967295
 */