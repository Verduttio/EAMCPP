#include <iostream>
#include <vector>
#include <list>
#include <deque>

using namespace std;

bool biggerThan5(int x){ return x>5; }

/// TODO
template<template<typename T, typename Alloc> typename OutContainer,
        template<typename T, typename Alloc> typename InContainer,
        typename T, typename Alloc,
        typename Predicate>
OutContainer<T,Alloc> selectIf(InContainer<T,Alloc>  c, Predicate p){
    OutContainer<T, Alloc> out;
    typename OutContainer<T, Alloc>::iterator it;
    for(T el : c) {
        it = out.end();
        if(p(el)) {
            out.insert(it, el);
        }
    }
    return out;
}


int main(){
    auto print = [](auto v) {
        for(auto x: v) cout << x << " ";
        cout << endl;
    };

    std::vector<int> v={1, 2, 13, 4, 5, 54};
    std::list<int> result = selectIf<std::list>(v, biggerThan5);
    print(result);  //  13 54

    auto result2 = selectIf<std::deque>(v, [](int x)->bool{ return x%2; } );
    print(result2); //  1 13 5

    auto result3 = selectIf<std::vector>(result2, biggerThan5);
    print(result3); //  13
    return 0;
}