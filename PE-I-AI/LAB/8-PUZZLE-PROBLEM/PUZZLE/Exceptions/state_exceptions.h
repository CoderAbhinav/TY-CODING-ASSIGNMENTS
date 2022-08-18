#pragma once
#include <iostream>

class StateExceptions : public std::exception {
private:
    std::string issue;

public:
    StateExceptions(std::string issue) {
        this->issue = issue;
    }

    virtual ~StateExceptions() throw() {}

    virtual char * what() const throw() {
        char* i = new char[issue.length() + 1];
        std::strcpy(i, this->issue.c_str());
        return i;
    }
};

class EmptyMatrixException : public StateExceptions {
public:
    EmptyMatrixException() : StateExceptions("State Matrix can't be empty") {}
};

class InvalidValuesException : public StateExceptions {
public:
    InvalidValuesException() : StateExceptions("Provided invalid values in matrix") {}
};
