#include <iostream>
#include <vector>
#include <typeinfo>
#include <list>
#include <boost/type_index.hpp>
using namespace std;


template <typename ... Ts>
class MultiVector{
public:
    MultiVector() {
        cout << "***MultiVector() base class***" << endl;
    }

    void print() {
        cout << endl;
    }
};

template <typename T, typename ... Ts>
class MultiVector<T,Ts...>:public MultiVector<Ts...>{
    vector<T> data;
    using Base = MultiVector<Ts...>;
public:

    MultiVector() {
        cout << "multiVector constructor" << endl;
        cout << "T: " << boost::typeindex::type_id<T>().pretty_name() << endl;
        cout << endl;
    }
    void push_back(T el)  {
        data.push_back(el);
    }

    template<typename S>
    void push_back(S el)  {
        Base::push_back(el);
    }

    void print() {
        cout << "[ ";
        for(auto el : data) {
            cout << el << " ";
        }
        cout << " ]";

        Base::print();
    }


};




int main(){

  MultiVector<int, string, double> m;
  m.push_back(5);
  m.push_back(string("text"));
  m.push_back(7);
  m.push_back(1.2);
  m.print();   // [ 5 7 ] [ text ] [ 1.2 ]
  auto v = std::move(m);
  for(auto x: { 1, 2, 3}){
	v.push_back(x+10);
	v.push_back(std::to_string(x));
	v.push_back(x/10.0);
  }
  m.print(); // [ ] [ ] [ ]   but can be undefined
  v.print(); // [ 5 7 11 12 13 ] [ text 1 2 3 ] [ 1.2 0.1 0.2 0.3 ]
  MultiVector<int, int, double, int> w;
  w.push_back(1);
  w.push_back(2.0);
  w.print(); // [ 1 ] [ ] [ 2 ] [ ]
}
/*
[ 5 7 ] [ text ] [ 1.2 ]
[ ] [ ] [ ]
[ 5 7 11 12 13 ] [ text 1 2 3 ] [ 1.2 0.1 0.2 0.3 ]
[ 1 ] [ ] [ 2 ] [ ]  
 */