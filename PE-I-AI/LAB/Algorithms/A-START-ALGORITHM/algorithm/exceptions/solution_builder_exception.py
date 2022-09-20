class SolutionBuilderException(Exception):
    def __init__(self, *args: object) -> None:
        super().__init__(*args)


class MissingArguments(Exception):
    def __init__(self, *args: object) -> None:
        super().__init__(*args)
    