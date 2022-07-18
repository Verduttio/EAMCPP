#include <type_traits>
#include <iostream>
#include <iomanip>

template<int N, typename T>
constexpr T ScalarProduct(T* a, T* b) {
    if constexpr (N>0) {
        return (a[N-1] * b[N-1]) + ScalarProduct<N-1>(a, b);
    }
    else {
        return 0;
    }
}


template<int M, int N, typename T>
constexpr void Multiply(T* A, T*x, T*y) {
    if constexpr(M > 0) {
        y[M - 1] = ScalarProduct<N>(A + (N) * (M - 1), x);
        Multiply<M-1, N>(A, x, y);
    }
}



using namespace std;
int main() {

    double a[] = {1, 2, 3};
    double b[] = {1, 1, 1};
    std::cout<< ScalarProduct<3>(a, b) << endl; // 6

    double x[] = {1, 1, 0};
    double A[] = {1, 0, 0,
                  2, -5, 1};
    double y[2];
    Multiply<2,3>(A, x, y);
    std::cout << y[0] << " " << y[1];  // 1 -3
}
