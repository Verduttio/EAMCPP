/*template<int ... Values> 
int sum(){
}

template <typename ...Ts>
void callFoo(Ts args...){}

template<template <typename, typename> class... Containers> 
void print(const Containers<int> & ... c);
*/
#include <iostream>
using namespace std;

template <typename ... Ts>
class Tuple{
	public:
	void print(){}
};

template <typename T, typename ... Ts>
class Tuple<T,Ts...>:public Tuple<Ts...>{
	using Base = Tuple<Ts...>;
   
   public:
   T data;
   Tuple(T t, Ts... ts) : Base(ts...), data(t){
   }
   void print(){
	   cout << data << " ";
	   Base::print();
   }
};


template <int index, typename T, typename ... Ts>
auto get(const Tuple<T, Ts...> & t){
    if constexpr (index ==0){
	 	//if constexpr (std::is_same_v<T, int>)
	 	  //  t.tratrata();
		return t.data;
		
	} else {
		return get<index -1> (static_cast<const Tuple<Ts...> &>(t));
	}
}

double multiply(){
	return 1.0;
}
template <typename T, typename ... Ts>
double multiply(T a, Ts... b){
	return a * multiply(b...);
}
template <typename ... Ts>
double multiply2(Ts... b){
	return (1.0 * ... * b);
}
int main(){
	cout << multiply(1, 2, 5.6, 3, 'A') << endl;
	cout << multiply2(1, 2, 5.6, 3, 'A') << endl;
	
	
	Tuple<int, double> t(1, 4.0);
	t.print();
	get<1>(t); 
	get<0>(t); 
	//sum<1,2,3,4,5>();
    //callFoo(1, "afdas", std::vector<int>{});
    //print<std::vector, std::list>(v, l); 
    	
}
