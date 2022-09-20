import imp


from queue import PriorityQueue
from .states import State

class Algorithm:


    class BreadthFirstSearch:
        def solver(self):
            q = [self.__initial]

            while len(q):
                curr = q.pop(0)

                if curr.key == self.__final.key:
                    self.__final = curr
                    break
                    
                children = self.__child_generator(curr)
                for child in children:
                    q.append(child)
                    curr.add_child(child)
                

        def __init__(self, initial: State, final: State, childGenerator) -> None:
            self.__initial = initial
            self.__final = final
            self.__child_generator = childGenerator

            self.solver()
        

        @property
        def final_state(self)->State:
            return self.__final

    
    class AStarAlgorithm:
        def solver(self):
            pq = PriorityQueue()
            pq.put((self.__heuristics(self.__initial), (0, self.__initial)))

            while pq.qsize():
                curr = pq.get()

                if curr[1].key == self.__final.key:
                    self.__final = curr[1]
                    break
                

                

                
                


        def __init__(self, initial: State, final: State, childGenerator, heuristics) -> None:
            self.__initial = initial
            self.__final = final
            self.__heuristics = heuristics

            