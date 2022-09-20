from algorithm.states import State
from algorithm.algorithms import Algorithm
from copy import deepcopy


def cg(st: State) -> list:
    cl = []
    max_rows = len(st.value)
    max_cols = len(st.value[0])
    posx, posy = -1, -1

    i = 0

    while i < max_rows:
        j = 0

        while j < max_cols:
            if st.value[i][j] == 0:
                posx, posy = i, j
                break
            j += 1

        i += 1
    

    def stateGen(x: int, y: int) -> State:
        csv = deepcopy(st.value)
        csv[posx][posy] = csv[x][y]
        csv[x][y] = 0

        return State(csv, parent=st)
    # up
    if posx > 0:
        cl.append(stateGen(posx - 1, posy))
    
    # down
    if posx < (max_rows - 1):
        cl.append(stateGen(posx + 1, posy))
    
    #left
    if posy > 0:
        cl.append(stateGen(posx, posy - 1))

    # right
    if posy < (max_cols - 1):
        cl.append(stateGen(posx, posy + 1))
    

    return cl


start = State([[0, 2, 3], [1, 8, 4], [7, 6, 5]])
end = State([[1, 2, 3], [8, 0, 4], [7, 6, 5]])

sol = Algorithm.BreadthFirstSearch(start, end, cg)

ans = []

temp = sol.final_state

while temp != None:
    ans.append(temp)
    temp = temp.parent


print(ans[::-1])

