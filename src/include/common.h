#ifndef COMMON_H
#define COMMON_H

#define FIXED_SIZE 512

char generate_rdrand64_ia32(float*, float, float);
// char* generate_range(unsigned int length);
char generate_rdrand64_boundary(int*, int);
char generate_rdrand64(int*, int);
char generate_rdrand64_bellow(int*, int);
char generate_rdseed(uint64_t*);
int rdrand_check_support();
int rdseed_check_support();

#endif