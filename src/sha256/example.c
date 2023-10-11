#include "sha256.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define L_ENDIAN	0
#define B_ENDIAN	1

static inline uint8_t endian() {
	int k = 1;
	char *p = (char *)&k;
	if (p[0] == 1)
        	return L_ENDIAN;
    	else
        	return B_ENDIAN;
}

static inline void to_uint32(uint8_t buffer[64], uint32_t buff[16]) {
        for (int i = 0; i < 64; i+=4) {
                buff[i/4] = buffer[i] << 24 | buffer[i+1] << 16 | buffer[i+2] << 8 | buffer[i+3];
        }
}

int main(int argc, char **argv) {
	sha256State_t state;
	
	FILE *file;
	file = fopen(argv[1], "rb");

	if (file == NULL) {
		return 1;
	}
	
	initState(&state);

	uint8_t buffer[64] = {0};
	while((state.message_length = fread(buffer, sizeof(uint8_t), 64, file))) {
		to_uint32(buffer, state.message);
		state.length += state.message_length;
		sha256(&state);
		memset(&state.message, 0x00, 16*sizeof(uint32_t));
		memset(&buffer, 0x00, 64*sizeof(uint8_t));
	}

	finalise(&state);

	return 0;
}
