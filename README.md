# Intel® Digital Random Number Generator for Python

This module is an interface for Intel's RDRAND instruction.

RDRAND (for "read random"; known as Intel Secure Key Technology, previously known as Bull Mountain) is an instruction for returning random numbers
from an Intel on-chip hardware random number generator which has been seeded by an on-chip entropy source.

RDRAND is available in Ivy Bridge processors and is part of the Intel 64 and IA-32 instruction set architectures. AMD added support for the instruction in June 2015.

See more: https://en.wikipedia.org/wiki/RDRAND

## Warning
Do not use **rdrand/rdseed** alone as a **CSPRNG**.

## Installation
```sh
# Clone this repo.
git clone https://github.com/trusted-ws/python-rdrand

# Inside the directory.
cd python-rdrand

# Using sudo, compile and install the module:
sudo build.sh install
```
## Testing
Open a Python 3x console and try to import:
```python
import rdrand
```
###### An ImportError should be raised in case of your CPU doesn't support rdrand.

## Resources
[Intel® Digital Random Number Generator (DRNG) Software Implementation Guide](https://www.intel.com/content/www/us/en/developer/articles/guide/intel-digital-random-number-generator-drng-software-implementation-guide.html)

[Intel® 64 and IA-32 Architectures Software Developer’s Manuals @ 7.3.17.1](https://www.intel.com/content/www/us/en/developer/articles/technical/intel-sdm.html)

