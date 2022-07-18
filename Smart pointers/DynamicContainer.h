#pragma once
#include <iostream>
#include <memory>
#include "Box.h"

using namespace std;

class Container{
    // Exercise 2: Use smart pointer.
    unique_ptr<Box> pbox = nullptr;
public:
    static bool verbose;
    Container(int content): pbox(make_unique<Box>(content)){
        if(verbose) cout << "Creating Container" << endl;
        pbox->setContent(content);
    }
    Container(const Container & container): pbox(make_unique<Box>(*container.pbox)){
        if(verbose) cout << "Creating copy of Container\n";
    }
    Container(Container&& container) noexcept : pbox(move(container.pbox)) {
        if(verbose) cout << "Making a move of Container\n";
    }


    Container & operator=(const Container &container){
        if(this != &container) {
            if(verbose) cout << "Copying Container\n";
            *pbox = *container.pbox;
        }
        return *this;
    }

    Container & operator=(Container&& container) noexcept {
        if(this != &container) {
            if(verbose) cout << "Moving Container\n";
            swap(container.pbox, pbox);
        }
        return *this;
    }

    ~Container(){
        if(verbose) cout << "Destroying Container \n";
    }
    friend Container operator+(const Container & p1, const Container & p2);
    friend std::ostream & operator << (std::ostream & out, const Container & p){
        return (out << " [" << p.pbox->getContent() << "] ");
    }
};

bool Container::verbose = false;

inline Container operator+(const Container & p1, const Container & p2){
    Container suma(p1.pbox->getContent() + p2.pbox->getContent());
    return suma;
}
