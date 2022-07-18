#include <iostream>
#include <list>
#include <vector>

using namespace std;

//https://en.cppreference.com/w/cpp/iterator/iterator_tags


template<typename Container>
double median_impl(Container set, std::forward_iterator_tag) {
    cout << "median_impl(Container set, std::forward_iterator_tag)" << endl;
    set.sort();

    size_t size = set.size();
    auto middle_index = size/2;
    /// Middle example
    // 1 2 3 4 5
    //     M
    // 1 2 3 4 5 6
    //       M

    bool compute_average = size % 2 == 0;
    auto middle_value = std::next(set.begin(), middle_index);

    if(compute_average) {
        return (*middle_value + *(--middle_value))/2.0;
    } else {
        return *middle_value;
    }
}

template<typename Container>
double median_impl(Container set, std::random_access_iterator_tag) {
    cout << "median_impl(Container set, std::random_access_iterator_tag)" << endl;
    sort(set.begin(), set.end());

    size_t size = set.size();
    auto middle_index = size/2;
    /// Middle example
    // 1 2 3 4 5
    //     M
    // 1 2 3 4 5 6
    //       M

    bool compute_average = size % 2 == 0;
    auto middle_value = std::next(set.begin(), middle_index);

    if(compute_average) {
        return (*middle_value + *(--middle_value))/2.0;
    } else {
        return *middle_value;
    }

}

template<typename Container>
double median(Container set) {
    using Iter = decltype(set.begin());
    return median_impl(set, typename std::iterator_traits<Iter>::iterator_category());
//    return median_impl(set, typename std::iterator_traits<typename Container::iterator>::iterator_category());
}


int main() {
    std::list<int> a{3, 2, 5, 1, 4};
    std::vector<int> v{3, 1, 4, 2};

    cout << median(a) << endl;
    cout << median(v) << endl;
}

