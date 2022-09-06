#pragma once
#include <unordered_map>
#include <string>
#include <queue>
#include <algorithm>
#include <iterator>
#include <string>
#include "state.h"
using namespace std;
class PuzzleSolverAStarAlgorithm
{
private:
    State *initial, *final;
    std::unordered_map<std::string, State*> stateMap;
    std::vector<State> required_moves;
    int explored_states, generated_states;

    void buildPath(State*, int);

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
    // this->required_moves = generateMoves();
}

void PuzzleSolverAStarAlgorithm::validate() {
    
}

void PuzzleSolverAStarAlgorithm::buildPath(State* curr, int level) {
    // std::cout << *curr;
    stateMap[curr->getKey()] = curr;
    if (curr->getKey() == final->getKey()) return;
    this->explored_states++;
    std::vector<State*> childrens = curr->getChildren();

    int eval = level + 1 + heuristics(*curr, *final);
    State* selection = childrens[0];

    for (int i = 1; i < childrens.size(); i++) {
        int curr_eval = (level + 1) + heuristics(*childrens[i], *final);
        this->generated_states++;
        if (curr_eval < eval) {
            selection = childrens[i];
        }
    }

    buildPath(selection, level + 1);
}

void PuzzleSolverAStarAlgorithm::Solve() {
    vector<vector<State*> > levels;

    levels.push_back(vector<State*>());
    levels[0].push_back(initial);
    cout << "EXPLORING";
    for (int i = 0; i < levels.size(); i++) {
        int local_min_f_score = INT16_MAX;
        vector<State*> possible_states;
        for (int j = 0; j < levels[i].size(); j++) {
            // cout << "EXP\n" << *levels[i][j];
            stateMap[levels[i][j]->getKey()] = levels[i][j];
            if (levels[i][j]->getKey() == final->getKey()) {
                goto ans;
            }

            vector<State*> childofcurr = levels[i][j]->getChildren();
            for (int k = 0; k < childofcurr.size(); k++) {
                possible_states.push_back(childofcurr[k]);
            }
        }
        for (int k = 0; k < possible_states.size(); k++) {
            int h = heuristics(*possible_states[i], *final);
            local_min_f_score = min(local_min_f_score, h);
        }
        cout << local_min_f_score << "\n";
        
        vector<State*> next_level;
        
        for (int k = 0; k < possible_states.size(); k++) {
            if (heuristics(*possible_states[i], *final) == local_min_f_score) {
                next_level.push_back(possible_states[i]);
            }
        }

        levels.push_back(next_level);
    }

    ans:
        // do nothing
        return;
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
    return this->required_moves.size() - 1;
}