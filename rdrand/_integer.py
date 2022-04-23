"""
Methods to work with integers.
"""
from typing import Optional


__all__ = [
    'uint_to_bytes',
    'uint_from_bytes',
    'int_to_bytes',
    'int_from_bytes',
]


def uint_to_bytes(x: int) -> bytes:
        return x.to_bytes((x.bit_length() + 7) // 8, 'big')


def uint_from_bytes(xbytes: bytes) -> int:
    return int.from_bytes(xbytes, 'big')


def int_to_bytes(x: int) -> bytes:
    return x.to_bytes(length=(8 + (x + (x < 0)).bit_length()) // 8, 
                      byteorder='big', signed=True)


def int_from_bytes(binary_data: bytes) -> Optional[int]:
    return int.from_bytes(binary_data, byteorder='big', signed=True)

