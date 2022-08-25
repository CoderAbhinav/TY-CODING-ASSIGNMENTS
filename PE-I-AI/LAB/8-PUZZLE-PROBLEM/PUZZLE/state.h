#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Exceptions/state_exceptions.h"
#define state_matrix std::vector<std::vector<int> >

template <typename T>
std::vector<std::vector<T> > copy2DVector(std::vector<std::vector<T> > original) {
    std::vector<std::vector<T> > duplicate(original.size(), std::vector<T>(original[0].size()));
    int rowCount = original.size(), colCount = original[0].size();

    for (int i = 0; i < rowCount; i++) {
        for (int j = 0; j < colCount; j++) {
            duplicate[i][j] = original[i][j];
        }
    }

    return duplicate;
}


class State
{
private:
    state_matrix matrix;
    std::string move; // [initial, final, up, down, left, right]
    std::string key;
    std::string parentKey;
    std::vector<State*> children;

    void validate();
public:
    State(state_matrix&, std::string, std::string);
    State(state_matrix&,std::vector<State*>);

    state_matrix getMatrix();
    std::string getKey();
    std::string getParentKey();
    std::pair<int, int> getEmptyCellLocation();
    std::vector<State*> getChildren();
    void setChildren(std::vector<State*>);
    void setMove(std::string);
    static std::string generateKey(std::vector<std::vector<int> >&);
    friend std::ostream& operator<<(std::ostream&, State);
    friend int heuristics(State, State);
};

void State::validate() {
    if (this->matrix.size() == 0) throw EmptyMatrixException();

    int rowCount = this->matrix.size(), colCount = this->matrix[0].size();

    std::vector<int> possibleValues(rowCount * colCount, 1);

    for (int i = 0; i < rowCount; i++) {
        for (int j = 0; j < colCount; j++) {
            if (possibleValues[matrix[i][j]] == 0) throw InvalidValuesException();
            else possibleValues[matrix[i][j]] = 0;
        }
    }
}

State::State(std::vector<std::vector<int> >& matrix, std::string parentKey = "-1", std::string move = "initial") {
    this->matrix =  matrix;
    this->parentKey = parentKey;
    this->move = move;
    
    validate();

    this->key = generateKey(this->matrix);
}

State::State(std::vector<std::vector<int> >& matrix, std::vector<State*> children) {
    this->matrix = matrix;
    this->children = children;

    this->key = generateKey(this->matrix);

    validate();
}

state_matrix State::getMatrix() {
    return copy2DVector(this->matrix);
}

std::string State::getKey() {
    return this->key;
}

std::string State::getParentKey(){
    return this->parentKey;
}

std::pair<int, int> State::getEmptyCellLocation() {
    int rowCount = matrix.size(), colCount = matrix[0].size();

    std::pair<int, int> loc;

    for (int i = 0; i < rowCount; i++) {
        for (int j = 0; j < colCount; j++) {
            if (matrix[i][j] == 0) {
                loc = std::make_pair(i, j);
                break;
            }
        }
    }

    return loc;
}

std::vector<State*> State::getChildren() {
    if (this->children.size() != 0) return this->children;

    std::pair<int, int> loc = getEmptyCellLocation();

    int rowCount = matrix.size(), colCount = matrix[0].size(), emptyRow = loc.first, emptyCol = loc.second;

    // up
    if (emptyRow > 0) {
        state_matrix childMatrix = copy2DVector(this->matrix);
        childMatrix[emptyRow][emptyCol] = childMatrix[emptyRow - 1][emptyCol];
        childMatrix[emptyRow - 1][emptyCol] = 0;
        this->children.push_back(new State(childMatrix, this->key, "up"));
    }
    // down
    if (emptyRow < (rowCount - 1)) {
        state_matrix childMatrix = copy2DVector(this->matrix);
        childMatrix[emptyRow][emptyCol] = childMatrix[emptyRow + 1][emptyCol];
        childMatrix[emptyRow + 1][emptyCol] = 0;
        this->children.push_back(new State(childMatrix, this->key, "down"));
    }
    // left
    if (emptyCol > 0) {
        state_matrix childMatrix = copy2DVector(this->matrix);
        childMatrix[emptyRow][emptyCol] = childMatrix[emptyRow][emptyCol - 1];
        childMatrix[emptyRow][emptyCol - 1] = 0;
        this->children.push_back(new State(childMatrix, this->key, "left"));
    }
    // right
    if (emptyCol < (colCount - 1)) {
        state_matrix childMatrix = copy2DVector(this->matrix);
        childMatrix[emptyRow][emptyCol] = childMatrix[emptyRow][emptyCol + 1];
        childMatrix[emptyRow][emptyCol + 1] = 0;
        this->children.push_back(new State(childMatrix, this->key, "right"));
    }

    return this->children;
}

void State::setChildren(std::vector<State*> children) {
    this->children = children;
}

void State::setMove(std::string move) {
    this->move = move;
}

std::string State::generateKey(std::vector<std::vector<int> >& v) {
    std::string key = "";
    int rowCount = v.size(), colCount = v[0].size();

    for (int i = 0; i < rowCount; i++) {
        for (int j = 0; j < colCount; j++) {
            key += std::to_string(v[i][j]);
        }
    }

    return key;
}

std::ostream& operator<<(std::ostream& os, State st) {
    os << "State{\nmatrix:\n";

    int rowCount = st.matrix.size(),colCount = st.matrix[0].size();

    for (int i = 0; i < rowCount; i++) {
        os << "[";
        for (int j = 0; j < colCount; j++) {
            os << std::to_string(st.matrix[i][j]) << " ";
        }
        os << "]\n";
    }

    os << "key: " << st.key 
    << ",\nparentKey: " <<  st.parentKey 
    << ",\nmove: " << st.move
    << "\n}" ;

    return os;
}

int heuristics(State current, State target) {
    int score = 0;

    for (int i = 0; i < current.key.length(); i++) {
        if (current.key[i] != target.key[i]) score++;
    }

    return score;
}