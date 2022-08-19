#include <iostream>
#include <vector>
#include "PUZZLE/state.h"
#include "PUZZLE/puzzle.h"
using namespace std;

vector<vector<int> > takeMatrix(int rows, int cols) {
    vector<vector<int> > v(rows, vector<int>(cols));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cin >> v[i][j];
        }
    }

    return v;
}



int main(int argc, char const *argv[])
{   

    vector<vector<int> > inm =  takeMatrix(3, 3);
    vector<vector<int> > fnm =  takeMatrix(3, 3);

    PuzzleSolver p(new State(inm), new State(fnm));

    vector<State> moves = p.getMoves();

    cout << "GENERATED STATES: " << p.getGeneratedStates() << ".\n";
    cout << "EXPLORED STATES: " << p.getExploredStates() << ".\n";
    cout << "NUMBER OF MOVES REQUIRED : " << p.getNumberOfMoves() << ".\n";
    cout << "\n\n\n";

    for (int i =0 ; i < moves.size(); i++) {
        cout << moves[i] << "\n\n\n";
    }

    return 0;
}
