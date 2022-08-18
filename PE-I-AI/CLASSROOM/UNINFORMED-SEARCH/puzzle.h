#pragma once
#include <vector>
#include <string>
#include <unordered_set>

std::vector<std::vector<int> > copyVector(std::vector<std::vector<int> >& matrix) {
    std::vector<std::vector<int> > cpy(matrix.size(), std::vector<int>(matrix[0].size()));
    
    int rowCount = matrix.size(), colCount = matrix[0].size();

    for (int i = 0; i < rowCount; i++) {
        for (int j = 0; j < colCount; j++) {
            cpy[i][j] = matrix[i][j];
        }
    }

    return cpy;
}

class State{
public:
    std::vector<std::vector<int> > matrix;
    std::string key;
    std::vector<State> children;
    State() {}
    State(std::vector<std::vector<int> >&);

    std::string getKey();

    friend std::ostream& operator<<(std::ostream&, State);
};

State::State(std::vector<std::vector<int> >& matrix) {
    this->matrix = matrix;
    this->key = getKey();
}

std::string State::getKey() {
    int rowCount = matrix.size(),colCount = matrix[0].size();

    std::string key = "";

    for (int i = 0; i < rowCount; i++) {
        for (int j = 0; j < colCount; j++) {
            key += std::to_string(matrix[i][j]);
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

    os << "key: " << st.key << " }";

    return os;
}

class PuzzleSolver{
public:
    State initial;
    State final;
    std::unordered_set<std::string> keySet;

    PuzzleSolver(State, State);

    State* next(State&, std::vector<State>&);
    std::vector<State> generateMoves();
    std::vector<State> buildChildren(State);
};

PuzzleSolver::PuzzleSolver(State initial, State final) {
    this->initial = initial;
    this->final = final;
}

State* PuzzleSolver::next(State& curr, std::vector<State>& ans) {
    // std::cout << curr << "\n";
    if (curr.key == final.key) return new State();
    keySet.insert(curr.key);

    curr.children = buildChildren(curr);

    for (int i = 0; i < curr.children.size(); i++) {
        if (keySet.count(curr.children[i].key) == 0) {
            std::cout << curr.children[i] << "\n";
            State* res = next(curr.children[i], ans);
            if (res != nullptr) {
                ans.push_back(*res);
                return res;
            }
        }

    }
    return nullptr;
}

std::vector<State> PuzzleSolver::generateMoves() {
    std::vector<State> ans;
    next(initial, ans);
    return ans;
}

std::vector<State> PuzzleSolver::buildChildren(State state) {
    std::vector<State> children;

    // find the empty bloc
    int rowCount = state.matrix.size(), colCount = state.matrix[0].size();
    int emptyRow = -1, emptyCol = -1;

    for (int i = 0; i < rowCount; i++) {
        for (int j = 0; j < colCount; j++) {
            if (state.matrix[i][j] == 0){
                emptyRow = i;
                emptyCol = j;
            }
        }
    }

    // up
    if (emptyRow > 0) {
        std::vector<std::vector<int> > child = copyVector(state.matrix);
        child[emptyRow][emptyCol] = child[emptyRow - 1][emptyCol];
        child[emptyRow - 1][emptyCol] = 0;
        children.push_back(State(child));
    }
    // down
    if (emptyRow < rowCount - 1) {
        std::vector<std::vector<int> > child = copyVector(state.matrix);
        child[emptyRow][emptyCol] = child[emptyRow + 1][emptyCol];
        child[emptyRow + 1][emptyCol] = 0;
        children.push_back(State(child));
    }
    // left
    if (emptyCol > 0) {
        std::vector<std::vector<int> > child = copyVector(state.matrix);
        child[emptyRow][emptyCol] = child[emptyRow][emptyCol - 1];
        child[emptyRow][emptyCol - 1] = 0;
        children.push_back(State(child));
    }
    // right
    if (emptyCol < colCount - 1) {
        std::vector<std::vector<int> > child = copyVector(state.matrix);
        child[emptyRow][emptyCol] = child[emptyRow][emptyCol + 1];
        child[emptyRow][emptyCol + 1] = 0;
        children.push_back(State(child));
    }

    return children;
}
