#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <cctype>
#include <ctime>
#include <thread>
#include <utility>
#include <thread>
#include <chrono>
using namespace std;

template <int N>
struct Array{
    int a[N];
    int i = 0;
    int j = 0;
    int k = 0;
	long long sum = 0;
    mutex mutex1;

	int f(int x){
		int y = x%11;
		return (y*y+1);
	}

	void generateArray(){
		while(true){
            lock_guard<mutex> l(mutex1);
            if(i < N) {
//                cout << "[GENERATING] - Thread ID: " << this_thread::get_id() << endl;

                a[i++] = rand();
//                auto val = (i*i)%43;
//                a[i++] = val;
            } else {
                break;
            }
		}
		while(true){
            lock_guard<mutex> l(mutex1);
            if(j < N) {
//                cout << "[COMPUTING] - Thread ID: " << this_thread::get_id() << endl;
                a[j] = f(a[j]);
                j++;
            } else {
                break;
            }
		}

	}
	
	long long computeSum(){
		while(true){
            lock_guard<mutex> l(mutex1);
//            cout << "[SUMMING] - Thread ID: " << this_thread::get_id() << endl;
            if(k < N) {
                sum += a[k++];
            } else {
                break;
            }
		}
		return sum;
	}
};

int main(){
	srand(2019);
	using A = Array<1000>;
	A array;
    int threadsNumber = 3;
    vector<thread> threads;

    auto start = chrono::steady_clock::now();

    // create threads
    threads.reserve(threadsNumber);
    for(int i = 0; i < threadsNumber; i++) {
        threads.emplace_back(&A::generateArray, &array);
    }
    // and wait until they finish
    for(int i = 0; i < threadsNumber; i++) {
        threads.at(i).join();
    }


    // after finishing remove them and create new ones
    threads.clear();
//    threadsNumber = 1;
    for(int i = 0; i < threadsNumber; i++) {
        threads.emplace_back(&A::computeSum, &array);
    }
    // and wait until they finish
    for(int i = 0; i < threadsNumber; i++) {
        threads.at(i).join();
    }

	for(int i=0; i<40; i++){
		cout << array.a[0+i] << "  ";
	}

	cout << "\n sum = " << array.sum << endl;

    auto end = chrono::steady_clock::now();

    cout << "\nTime: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microsecs" << endl;
}
