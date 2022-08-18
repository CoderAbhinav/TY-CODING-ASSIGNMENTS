#pragma once
#include <unordered_map>
#include <string>
#include <queue>
#include <algorithm>
#include <string>
#include "state.h"


class PuzzleSolver
{
private:
    State *initial, *final;
    std::unordered_map<std::string, State*> stateMap;
    std::vector<State> required_moves;
    int explored_states, generated_states;

    void Solve();
    void validate();
    std::vector<State> generateMoves();

public:
    PuzzleSolver(State*, State*);

    std::vector<State> getMoves();
    int getExploredStates();
    int getGeneratedStates();
    int getNumberOfMoves();
};

PuzzleSolver::PuzzleSolver(State* initialState, State* finalState) {
    this->initial = initialState;
    this->final = finalState;
    this->explored_states = 0;
    this->generated_states = 0;
    Solve();
    this->required_moves = generateMoves();

}

void PuzzleSolver::validate() {

}

void PuzzleSolver::Solve() {
    int exploredState = 0;
    std::queue<State*> q;
    q.push(initial);
    stateMap[initial->getKey()] = initial;

    while (q.size())
    {
        this->explored_states++;
        State* curr = q.front();
        q.pop();
        
        if (curr->getKey() == final->getKey()) {
            break;
        }

        std::vector<State*> children = curr->getChildren();

        for (int i = 0; i < children.size(); i++) {
            if (stateMap.count(children[i]->getKey()) == 0) {
                q.push(children[i]);
                stateMap[children[i]->getKey()] = children[i];
                this->generated_states++;
            }
        }
    }
}



std::vector<State> PuzzleSolver::generateMoves() {
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

std::vector<State> PuzzleSolver::getMoves() {
    return this->required_moves;
}

int PuzzleSolver::getExploredStates() {
    return this->explored_states;
}

int PuzzleSolver::getGeneratedStates() {
    return this->generated_states;
}

int PuzzleSolver::getNumberOfMoves() {
    return this->required_moves.size();
}