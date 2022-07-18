#include <iostream>
#include <typeinfo>
#include <boost/type_index.hpp>
using namespace std;

double f(int x, double y, const int & z, int & w){
    w += 2;
	cout << x << " " << y<< " " << z << " " << w <<endl;
	return (x*y - z*w);
}

template<typename T>
void showTypes(T&& arg) {
    auto type = boost::typeindex::type_id_with_cvr<T>();
    cout << "from end " << 1 << " > " << type.pretty_name()
    << " ["  << type.raw_name() << "] " << " = " << arg << endl;
}

template<typename T, typename ...Types>
void showTypes(T&& arg1, Types&& ... args) {
    auto type = boost::typeindex::type_id_with_cvr<T>();
    cout << "from end " << sizeof...(args) + 1 << " > " << type.pretty_name() << " "
         << "["  << type.raw_name() << "] " << " = " << arg1 << endl;
    showTypes(std::forward<Types>(args)...);
}

template<typename T>
class Proxy {
    T functor;
public:
    explicit Proxy(T functor) : functor(functor) {}

    template<typename ...Types>
    double operator() (Types&&... args) {
        cout << "\nProxy" << endl;
        showTypes(forward<Types>(args)...);
        return functor(std::forward<Types>(args)...);
    }

};

template<typename T>
Proxy<T> make_proxy(T functor) {
    return Proxy<T>(functor);
}

int main(){

    int x = 4;
    const int y = 8;
    showTypes(x, 4.5, y, f);
    showTypes(1, 1.0f, 1.0, 1LL, &x, &y);

    auto p = make_proxy(f);
//    auto p = Proxy(f);    /// with C++ 17
    auto result1 = p(12, 5.1, y, x);
    cout << "result1 = " << result1 << endl;
    auto result2 = p(12, 5.1, y, x);
    cout << "result2 = " << result2 << endl;
    auto result3 = p(3, 3, 5, x);
    cout << "result3 = " << result3 << endl;

//    auto g = make_proxy([](int &&x, int & y){ y = x; return y; }) ;
    auto g = Proxy([](int &&x, int & y){ y = x; return y; }) ; // with C++ 17
  //  auto g = make_proxy([](int &&x, int  &y){ y = x; return y; }) ;
    cout << g(5, x) << endl;
    cout << "x = " <<  x << endl;
    return 0;
}
/** Expected output 
 1 > int& [i] = 4
 2 > double [d] = 4.5
 3 > int const& [i] = 8
 4 > double (&)(int, double, int const&, int&) [FdidRKiRiE] = 1
 1 > int [i] = 1
 2 > float [f] = 1
 3 > double [d] = 1
 4 > long long [x] = 1
 5 > int* [Pi] = 0x7ffde80f14c4
 6 > int const* [PKi] = 0x7ffde80f14c0

Proxy
 1 > int [i] = 12
 2 > double [d] = 5.1
 3 > int const& [i] = 8
 4 > int& [i] = 4
12 5.1 8 6
result1 = 13.2

Proxy
 1 > int [i] = 12
 2 > double [d] = 5.1
 3 > int const& [i] = 8
 4 > int& [i] = 6
12 5.1 8 8
result2 = -2.8

Proxy
 1 > int [i] = 3
 2 > int [i] = 3
 3 > int [i] = 5
 4 > int& [i] = 8
3 3 5 10
result3 = -41

Proxy
 1 > int [i] = 5
 2 > int& [i] = 10
5
x = 5
*/
