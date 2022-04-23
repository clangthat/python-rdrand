import _rdrand


__all__ = [
    'randint',
    'randbelow',
]

def randint(a: int, b: int) -> int: 
    """Generate a random number in the range [a, b]"""
    raise NotImplementedError


def randbelow(n: int) -> int:
    """Generate a number in range [0, n]"""
    raise NotImplementedError

