//
// Created by Bartek on 2022-04-04.
//

#ifndef LAB_05_VECTOREXCEPTION_H
#define LAB_05_VECTOREXCEPTION_H

#include <iostream>
#include <exception>

class VectorException : public std::runtime_error {
    const char *message;
public:
    explicit VectorException(const char *message) : std::runtime_error(message), message(message){}

    const char * what () const noexcept override
    {
        return message;
    }
};


#endif //LAB_05_VECTOREXCEPTION_H
