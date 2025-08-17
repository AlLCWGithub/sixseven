#ifndef RANDOMCORE_H
#define RANDOMCORE_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C"{
#endif

void rcseed(uint64_t seed);
uint64_t rcuint64();

#ifdef __cplusplus
}
#endif

#endif
