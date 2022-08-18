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