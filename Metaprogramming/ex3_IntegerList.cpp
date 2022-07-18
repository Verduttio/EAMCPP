#include <type_traits>
#include <iostream>
#include <iomanip>

template <int...>
class IntegerList {

};

template<int first, int... rest>
class IntegerList <first, rest...>{
public:
    static constexpr int get(int index) {
        if(index == 0) {
            return first;
        } else {
            return IntegerList<rest...>::get(--index);
        }
    }

    template<int tmp = first>
    static constexpr int max() {
        if(first > tmp) {
            return IntegerList<rest...>::template max<first>();
        } else {
            return IntegerList<rest...>::template max<tmp>();
        }
    }

    template<int previous = first>
    static constexpr bool isSorted() {
        if(first >= previous) {
            return IntegerList<rest...>::template isSorted<first>();
        } else {
            return false;
        }
    }
};

template<int single>
class IntegerList <single>{
public:
    static constexpr int get(int index) {
        return single;
    }

    template<int tmp>
    static constexpr int max() {
        if(single > tmp) {
            return single;
        } else {
            return tmp;
        }
    }

    template<int previous>
    static constexpr bool isSorted() {
        if(single >= previous) {
            return true;
        } else {
            return false;
        }
    }

};


template<int... args>
std::ostream &operator<<(std::ostream & out, const IntegerList<args...> &integerList) {
    ((out << args  << " "), ...);
    return out;
}

template<int index, class IntegerList>
class getInt {
public:
    static constexpr int value = IntegerList::get(index);
};

template<class IntegerList>
class IsSorted {
public:
    static constexpr bool value = IntegerList::isSorted();
};

template<class IntegerList>
class Max {
public:
    static constexpr int value = IntegerList::max();
};

template<class IntegerList1, class IntegerList2>
class Join {
};

template<int... first, int... second>
class Join<IntegerList<first...>, IntegerList<second...>>{
public:
    using type = IntegerList<first..., second...>;
};

using namespace std;
int main() {

    using listA = 	IntegerList<5, -1, 5, 2, 1>;
    using listB =   IntegerList<1, 4, 6, 9>;
    cout << "List A : " << listA() << endl;
    cout << "List B : " << listB() << endl;

    cout << "A[1] = " << getInt<1, listA>::value << endl;
    cout << "B[3] = " << listB::get(3) << endl;
    static_assert( getInt<1, listA>::value == -1 );
    static_assert( listB::get(3) == 9 );
    static_assert( listB::get(1) == 4 );

    cout << boolalpha;
    cout << "Is A sorted? " << IsSorted<listA>::value << endl;
    cout << "Is B sorted? " << IsSorted<listB>::value << endl;

    using listC = Join<listA, listB>::type;

    cout << "List C : " << listC() << endl;
    cout << Max<listC>::value << endl;
    cout << listC::max() << endl;
    static_assert(listC::max() == 9 );
    static_assert(listA::max() == 5 );

}
