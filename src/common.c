#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdlib.h>
#include <stdint.h>

#include "include/common.h"
#include "include/rdrand.h"


char generate_rdrand64_ia32(float *randf, float min, float max) {
    int retries = 10;
    unsigned long long rand64;

    while(retries--) {
        if(__builtin_ia32_rdrand64_step(&rand64)) {
            *randf = (float) rand64 / ULONG_MAX * (max - min) + min;
            return 1;
        }
    }
    return 0;
}

char generate_rdrand64(int *number, int max) {

    uint64_t retn;

    if (rdrand_check_support() == 1) {
        rdrand_get_uint64_retry(10, &retn);
        *number = (int) retn % max;
    } else {
        fprintf(stderr, "RDRAND instruction not supported.\n");
        return -1;
    }
    return 0;
}

char generate_rdrand64_bellow(int *number, int bellow) {
    
    uint64_t retn;
    int m, v;

    if (rdrand_check_support() == 1) {
        rdrand_get_uint64_retry(10, &retn);
        
        v = (int) retn % (bellow - 1);
        m = v >> sizeof(int) * (__CHAR_BIT__ - 1);
        *number = (int) (v + m) ^ m;
    } else {
        fprintf(stderr, "RDRAND instruction not supported.\n");
        return -1;
    }

    return 0;
}

char generate_rdrand64_boundary(int *number, int boundary) {
    
    uint64_t retn;
    int m, v;

    if(rdrand_check_support() == 1) {
        
        rdrand_get_uint64_retry(10, &retn);

        v = (int) retn % (boundary + 1);
        m = v >> sizeof(int) * (__CHAR_BIT__ - 1);
        *number = (int) (v + m) ^ m;
    
    } else {
        fprintf(stderr, "RDRAND instruction not supported.\n");
        return -1;
    }
    
    return 0;
}

char generate_rdseed(uint64_t *number) {
    
    if (rdseed_check_support() == 1) {
        rdseed_get_uint64_retry(10, number);
        return 0;
    }

    fprintf(stderr, "RDSEED instruction isn't supported.");
    return -1;

}

// char* generate_range(unsigned int length) {

//     int randf;
//     char* output = malloc(FIXED_SIZE);
//     int array[91] = { 0 };
//     int pos = 0;


//     memset(output, 0, FIXED_SIZE);

//     if(length > 90) {
//         printf("Length must be in the following range: 1-90. %d given.\n", length);
//         return "-1";
//     }

//     while (1) {
        
//         int insert = 1;
        
//         if (!generate_rdrand64(&randf)) {
//             for (int i = 0; i < length; i++) {
//                 if (array[i] == (int) randf) {
//                     insert = 0;
//                     break;
//                 }
//             }

//             if (pos == length) {
//                 break;
//             }

//             if (insert) {
//                 array[pos] = (int) randf;
//                 pos++;
//             }
//         } else {
//             perror("Failed to get random value.");
//             exit(2);
//         }
//     }

//     for (int i = 0; i < length; i++) {
//         if (i == length - 1) {
//             sprintf(output + strlen(output), "%d", (int) array[i]);
//         } else {
//             sprintf(output + strlen(output), "%d-", (int) array[i]);
//         }
//     }

//     return output;
// }