// Copyright (c) 2022 murilo
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT


#ifndef COMMON_H
#define COMMON_H

#define FIXED_SIZE 512
#define BPF 53

char generate_rdrand64_ia32(float*, float, float);
// char* generate_range(unsigned int length);
char generate_rdrand64_boundary(int*, int);
char generate_rdrand64(uint64_t*);
char generate_rdrand64_below(int*, int);
char generate_rdseed(uint64_t*);
int rdrand_check_support();
int rdseed_check_support();
unsigned int absolute(int);
#endif