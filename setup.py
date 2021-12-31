from distutils.core import setup
from distutils.extension import Extension

sources = [
    'src/common.c',
    'src/rdrand.c',
    'src/main.c'
]

extra_args = [
    '-mrdrnd'
]

module = Extension('rdrand', sources=sources)

setup(
    name="Python RDRAND",
    version="1.0",
    description="Python Interface for RDRAND functions",
    ext_modules=[module],
    extra_compile_args=extra_args
)