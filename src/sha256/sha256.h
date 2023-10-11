#ifndef SHA256_H
#define SHA256_H

#include <stdint.h>

typedef struct sha256State {
	uint32_t W[64];
	uint32_t message[16];
        uint32_t H[8];
        uint32_t message_length;
        uint64_t length;
        uint8_t finalised;
} sha256State_t;

void initState(sha256State_t *state);

void sha256(sha256State_t *state);

void finalise(sha256State_t *state);

#endif
