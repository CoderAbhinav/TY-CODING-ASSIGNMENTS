# The 8 Puzzle Problem

## How to use ?
1. Add puzzle folder & import
```
#include "PUZZLE/state.h"
#include "PUZZLE/puzzle.h"
```

2. Create the initial and final state

```
State(state_matrix)
```

3. Create PuzzleSolverObject & provide initial & final state
```
PuzzleSolve(initial, final)
```

4. Get different solution parameters, you can get following
```
getMoves() -> return intermediate states between the initial and final
getExploredState() -> returns count of generated states
getGeneratedState() -> value of generated states
getNumberOfMoves() -> return moves required
```

5. State model
```
{
    "matrix", // example [[1, 2, 3], [8, 0, 4], [7, 6, 5]]
    "key", // example 123804765
    "parentKey", // example 123084765
    "move", // any value in [inital, final, up, down, left, right]
    "children" // vector of states
}
```

## INPUT
```
0 1 3
7 2 4
6 8 5

1 2 3
8 0 4
7 6 5
```

## OUTPUT
```
GENERATED STATES: 122.
EXPLORED STATES: 73.
NUMBER OF MOVES REQUIRED : 7.



State{
matrix:
[0 1 3 ]
[7 2 4 ]
[6 8 5 ]
key: 013724685,
parentKey: -1,
move: initial
}


State{
matrix:
[1 0 3 ]
[7 2 4 ]
[6 8 5 ]
key: 103724685,
parentKey: 013724685,
move: right
}


State{
matrix:
[1 2 3 ]
[7 0 4 ]
[6 8 5 ]
key: 123704685,
parentKey: 103724685,
move: down
}


State{
matrix:
[1 2 3 ]
[7 8 4 ]
[6 0 5 ]
key: 123784605,
parentKey: 123704685,
move: down
}


State{
matrix:
[1 2 3 ]
[7 8 4 ]
[0 6 5 ]
key: 123784065,
parentKey: 123784605,
move: left
}


State{
matrix:
[1 2 3 ]
[0 8 4 ]
[7 6 5 ]
key: 123084765,
parentKey: 123784065,
move: up
}


State{
matrix:
[1 2 3 ]
[8 0 4 ]
[7 6 5 ]
key: 123804765,
parentKey: 123084765,
move: right
}
```