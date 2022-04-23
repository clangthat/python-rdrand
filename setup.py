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

module = Extension('_rdrand', sources=sources)

setup(
    name="rdrand",
    version="1.3",
    description="Intel® - Digital Random Number Generator (DRNG) [Bull Mountain] interface for Python.",
    author="Murilo Augusto",
    ext_modules=[module],
    extra_compile_args=extra_args,
    packages=['rdrand'],
)
