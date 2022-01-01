#ifndef __PYCDEF__
#define __PYCDEF__

#define rdrand__doc__                                                   \
    "Intel's RDRAND/RDSEED interface for Python 3.9"

#define range__doc__                                                    \
    "range(length, boundary=90)\n"                                      \
    "--\n\n"                                                            \
    "Generate a non-repeated random range with specified length."       \

#define randint__doc__                                                  \
    "randint(min, max)\n"                                               \
    "--\n\n"                                                            \
    "Generate a range between min, max (positive)."                     \

#define range_bellow__doc__                                             \
    "range_bellow(length, bellow)\n"                                    \
    "--\n\n"                                                            \
    "Generate a N positive integers bellow."                            \

#define n_range_bellow__doc__                                           \
    "n_range_bellow(length, bellow, amount)\n"                          \
    "--\n\n"                                                            \
    "Generate a N-sized array with 'length' positive integers bellow."  \

#define is_rdrand_supported__doc__                                      \
    "is_rdrand_supported()\n"                                           \
    "--\n\n"                                                            \
    "Check if rdrand instruction is supported by current CPU."          \

#define is_rdseed_supported__doc__                                      \
    "is_rdseed_supported()\n"                                           \
    "--\n\n"                                                            \
    "Check if rdseed instruction is supported by current CPU."          \

#define rdseed__doc__                                                   \
    "rdseed()\n"                                                        \
    "--\n\n"                                                            \
    "Return an int converted from uint64_t using  rdseed instruction."  \

#endif