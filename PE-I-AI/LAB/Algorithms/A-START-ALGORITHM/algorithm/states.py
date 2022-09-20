from typing import Any


class State:
    """
    State class represents a praticular state in machine
    """

    
    def __init__(self, state_value, children : list = None, parent = None) -> None:
        """Creates a state objects & generates a key

        Arguments:
            state_value: dynamic
            children: set()
            parent_key: int
        
        Returns:
            None
        """
        
        self.__state_value = state_value
        if children is None:
            self.__children = []
        else:
            self.__children = children
        self.__parent = parent
        self.__key = hash(tuple([tuple(l) for l in self.__state_value]))


    @property
    def value(self) -> Any:
        """
        Returns value of current state

        Return:
            Any
        """
        return self.__state_value
    

    @property
    def key(self) -> int:
        """
        Returns hashkey for current state

        Return:
            int
        """
        return self.__key


    @property
    def children(self) -> list:
        """
        Return list of child states

        Return:
            set()
        """
        return self.__children


    @property
    def parent(self):
        return self.__parent


    def add_child(self, child) -> bool:

        """
        Adds a new children to children set,
        returns false if the children is already present

        Arguments:
            child : State

        Returns:
            bool

        """

        if (child in self.children):
            return False

        self.children.append(child)

        return True


    def remove_child(self, child) -> bool:
        """
        removes a children from children set,
        returns false if the children is not present

        Arguments:
            child : State

        Returns:
            bool

        """
        if (child not in self.children):
            return False

        self.children.remove(child)
        return True


    def __repr__(self) -> str:
        """
        Returns string representation of State

        Returns:
            str
        """
        return f"State(key: {self.__key}\nstate_value: {self.__state_value}\nchildren_count: {len(self.__children)})"