#pragma once
#include <iostream>

class PuzzleSolverExceptions : public std::exception {
private:
    std::string issue;

public:
    PuzzleSolverExceptions(std::string issue){
        this->issue = issue;
    }

    virtual ~PuzzleSolverExceptions() throw() {}

    char * what() const throw() {
        char* i = new char[issue.length() + 1];
        std::strcpy(i, this->issue.c_str());
        return i;
    }
};

class InvalidDimentionException : public PuzzleSolverExceptions {
    InvalidDimentionException() : PuzzleSolverExceptions("The dimentions for initial and final state matrix doesn't match") {}
};

class UnrechableFinalStateException : public PuzzleSolverExceptions {
    UnrechableFinalStateException() : PuzzleSolverExceptions("Can't reach to goal state as values are different than initial state") {}
};