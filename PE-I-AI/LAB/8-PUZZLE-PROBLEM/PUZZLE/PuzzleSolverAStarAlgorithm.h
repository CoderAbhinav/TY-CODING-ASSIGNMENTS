#pragma once
#include <unordered_map>
#include <string>
#include <queue>
#include <algorithm>
#include <string>
#include "state.h"

class PuzzleSolverAStarAlgorithm
{
private:
    State *initial, *final;
    std::unordered_map<std::string, State*> stateMap;
    std::vector<State> required_moves;
    int explored_states, generated_states;

    void buildPath(State*);

    void Solve();
    void validate();
    std::vector<State> generateMoves();
public:
    PuzzleSolverAStarAlgorithm(State*, State*);

    std::vector<State> getMoves();
    int getExploredStates();
    int getGeneratedStates();
    int getNumberOfMoves();
};

PuzzleSolverAStarAlgorithm::PuzzleSolverAStarAlgorithm(State* initialState, State* finalState)
{
    this->initial = initialState;
    this->final = finalState;
    this->explored_states = 0;
    this->generated_states = 0;
    Solve();
    this->required_moves = generateMoves();
}

void PuzzleSolverAStarAlgorithm::validate() {

}

void PuzzleSolverAStarAlgorithm::buildPath(State* curr) {
    // std::cout << *curr;
    stateMap[curr->getKey()] = curr;
    if (curr->getKey() == final->getKey()) return;
    this->explored_states++;
    std::vector<State*> childrens = curr->getChildren();
    int eval = 1 + heuristics(*curr, *final);
    State* selection = childrens[0];

    for (int i = 1; i < childrens.size(); i++) {
        int curr_eval = 1 + heuristics(*childrens[i], *final);
        this->generated_states++;
        if (curr_eval < eval) {
            selection = childrens[i];
        }
    }

    buildPath(selection);
}

void PuzzleSolverAStarAlgorithm::Solve() {
    buildPath(initial);
}

std::vector<State> PuzzleSolverAStarAlgorithm::generateMoves() {
    State* temp = stateMap[final->getKey()];
    std::vector<State> ans;
    while (temp->getParentKey() != "-1")
    {
        ans.push_back(*temp);
        // std::cout << *temp << "\n--\n";
        temp = stateMap[temp->getParentKey()];
    }

    ans.push_back(*initial);
    std::reverse(ans.begin(), ans.end());

    return ans;
}

std::vector<State> PuzzleSolverAStarAlgorithm::getMoves() {
    return this->required_moves;
}

int PuzzleSolverAStarAlgorithm::getExploredStates() {
    return this->explored_states;
}

int PuzzleSolverAStarAlgorithm::getGeneratedStates() {
    return this->generated_states;
}

int PuzzleSolverAStarAlgorithm::getNumberOfMoves() {
    return this->required_moves.size();
}