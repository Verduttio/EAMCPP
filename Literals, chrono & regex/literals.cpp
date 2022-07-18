#include <iostream>
using namespace std;


double operator "" _C (long double x){
    return x;
}

double operator "" _C (unsigned long long x){
    return x;
}

double operator "" _K (long double x){
    return x - 273.15;
}
double operator "" _K (unsigned long long x){
    return (double)x - 273.15;
}
double operator "" _F (long double x){
    return (x - 32)* 5. / 9.;
}
double operator "" _F (unsigned long long x){
    return  ((double)x - 32) * 5. / 9.;
  // return  (x - 32) * 5. / 9.;
}

std::string operator "" _op (const char * s, size_t n){
    std::string text = "";
    for(int i=0; i<n; ++i){
        text += "["s + s[i] + "]"s;
    }
    return text;
}
int main(){
    auto x =  4u;
    auto y = 4.0f;

    double temperature = 13.32;

    auto s = "text"s;
    cout << s+s <<endl;

    auto temp1 = 12_C;
    auto temp2 = 322_K;

   //Climate c(15_C, 1010_hPa, 80_percent);

    cout << temp1 << endl;
    cout << temp2 << endl;
    cout << 14_F << endl;

    cout << "abcde"_op << endl;
    return 0;
}
