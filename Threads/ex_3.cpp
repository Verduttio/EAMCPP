#include <iostream>
#include <fstream>
#include <future>
#include <thread>
#include <vector>

using namespace std;

void countChars(const string& fileName, promise<int>&& sum) {
    fstream file;
    file.open(fileName, ios::in);

    int sum_tmp = 0;
    while(true) {
        char tmp;
        file >> tmp;
        if(file.eof())
            break;
        sum_tmp += tmp;
    }
    sum.set_value(sum_tmp);
    file.close();
}

void printSizes(vector<int> sums, char* argv[]) {
    for(int i = 0; i < sums.size(); i++) {
        if(sums.at(i) != -1) {
            int val = sums.at(i);
            cout << "sum " << val << ": " << argv[i + 1];
            for (int j = i + 1; j < sums.size(); j++) {
                if (sums.at(j) == val) {
                    cout << ", " << argv[j + 1];
                    std::replace(sums.begin(), sums.end(),val, -1);
                }
            }
            cout << endl;
        }
    }
}


int main(int argc, char* argv[]) {
    int size = argc-1;
    future<int> sums [size];
    vector<thread> threads;

    threads.reserve(size);
    for(int i = 0; i < size; i++) {
        promise<int> promise;
        sums[i] = promise.get_future();
        threads.emplace_back(countChars, argv[i+1], move(promise));
    }


    cout << sums[0].get()<< endl;
    cout << sums[0].get()<< endl;
//    vector<int> sums_v;
//    sums_v.reserve(size);
//    for(int i = 0; i < size; i++) {
//        sums_v.push_back(sums[i].get());
//    }
//    printSizes(sums_v, argv);
//

    for(int i = 0; i < size; i++) {
        threads.at(i).join();
    }

    return 0;
}