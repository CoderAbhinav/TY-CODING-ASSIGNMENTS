#include <iostream>
#include "puzzle.h"
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
    cout << "initial\n";
    vector<vector<int> > inm = takeMatrix(3, 3);
    State initial(inm);
    cout << "final\n";
    vector<vector<int> > fnm = takeMatrix(3, 3);
    State final(fnm);
    cout << initial << "\n" << final;
    PuzzleSolver p(initial, final);

    vector<State> res = p.generateMoves();

    for (int i = 0; i < res.size(); i++) {
        cout << res[i] << "\n";
    }

    return 0;
}
