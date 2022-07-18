#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iterator>
#include <map>
#include <chrono>

using namespace std;

/**
 * Removes all non alphanumeric characters from given word and converts to lower case.
 * @param[in,out] word on return word consist only of lower case characters.
 */
void toLowerAlpha(std::string & s1) {
    //2. Implement using stl algorithms only
    //   Hint: use remove_if, transform, erase
    ///https://en.cppreference.com/w/cpp/algorithm/remove
    s1.erase(std::remove_if(s1.begin(), s1.end(), [](unsigned char x){return !std::isalnum(x);}), s1.end());
    std::transform(s1.begin(), s1.end(), s1.begin(), [](unsigned char x){return std::tolower(x);});
}

int main(){
    auto start = chrono::steady_clock::now();
    std::string word;
    unordered_map<string, int> c;
    std::vector<int> v;
    while( cin >> word) {
       toLowerAlpha(word);

       if(!word.empty()){
           c[word]++;
       }

    }

    // ...
    multimap<int, string> m2;
    std::transform(c.begin(), c.end(), std::inserter(m2, m2.begin()),
                   [](const std::pair<std::string,int>& p) {
                       return std::pair<int, std::string>(p.second, p.first);
                   });


    cout << "Number of distinct words : " << c.size() << endl;
    cout << "\nThe top 20 most popular words: \n";

    for (auto it = m2.rbegin(); it != std::next(m2.rbegin(), 21); it++) {
        std::cout << it->second << " : " << it->first << std::endl;
    }

    auto end = chrono::steady_clock::now();
    cout << "Elapsed time in milliseconds: "
         << chrono::duration_cast<chrono::milliseconds>(end - start).count()
         << " ms" << endl;

    ///Average time: 48ms

    return 0;
}
/*
 * Expected output for ./words < hamletEN.txt

Number of distinct words : 4726

The top 20 most popular words:
the : 1145
and : 967
to : 745
of : 673
i : 569
you : 550
a : 536
my : 514
hamlet : 465
in : 437
it : 417
that : 391
is : 340
not : 315
lord : 311
this : 297
his : 296
but : 271
with : 268
for : 248
your : 242

 */