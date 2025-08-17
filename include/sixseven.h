#ifndef SIXSEVEN_H
#define SIXSEVEN_H

#include <stdint.h>

#ifdef __cplusplus
extern "C"{
#endif

void ssseed(uint64_t seed);
int ssint(int min, int max);
double ssdouble();
void ssbytes(unsigned char *buffer, int length);
uint64_t ssuint64();

#ifdef __cplusplus
}
#endif

#endif
