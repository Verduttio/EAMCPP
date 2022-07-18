#include <iostream>
#include <algorithm>
#include "MyString.h"
#include <memory>
using namespace std;

class String{
   using string = emcpp::MyString;
//    using string = std::string;

/// Store a pointer to dynamically allocated string!
    shared_ptr<string> obj = nullptr;

public:
    String() : obj(make_shared<string>()) {};     /// creates an empty string
    explicit String(const char * str) : obj(make_shared<string>(str)) {};           /// copy C-string
    //String(const String & s) : obj(shared_ptr<string>(s.obj)) {};            /// no copy
    String(const String & s) = default;            /// no copy
    String& operator=(const String & s) { /// no copy
        obj = s.obj;
        return *this;
    };
    /// makes a copy of a string if it has more than one reference.
    void set(int index, char ch) {
        if(obj.use_count() > 1) {
            obj = make_shared<string>(*obj);
        }
        obj->at(index) = ch;
    }
    /// no copy
    char get(int index) const {
        return obj->at(index);
    }
    /// creates a new string only if both strings are non empty
    friend String operator+(String a, String b) {
        if (!a.obj->empty()) {
            if (!b.obj->empty()) {
                return String(((*a.obj) + (*b.obj)).c_str());
            } else {
                return a;
            }
        } else {
            if (!b.obj->empty()) {
                return b;
            }
        }
    };
    friend std::ostream & operator<< (std::ostream & out, String s) {
        out << *(s.obj);
        return out;
    }
};
