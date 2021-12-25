#ifndef __PYCDEF__
#define __PYCDEF__

#define generate_range__doc__                                           \
    "generate_range(length)\n"                                          \
    "--\n\n"                                                            \
    "Generate a non-repeated random range with specified length."       \

#define randint__doc__                                                  \
    "randint(min, max)\n"                                               \
    "--\n\n"                                                            \
    "Generate a range between min, max (positive)."                     \

#define generate_range_bellow__doc__                                    \
    "generate_range_bellow(length, bellow)\n"                           \
    "--\n\n"                                                            \
    "Generate a N positive integers bellow."                            \

#define generate_n_range_bellow__doc__                                  \
    "generate_n_range_bellow(length, bellow, amount)\n"                 \
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

#endif