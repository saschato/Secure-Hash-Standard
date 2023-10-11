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

int main(int argc, char **argv) {
	sha256State_t state;
	
	FILE *file;
	file = fopen(argv[1], "rb");

	if (file == NULL) {
		return 1;
	}
	
	initState(&state);

	uint8_t buffer[BUFFSIZE] = {0};
    uint32_t b_len = 0;
	while((b_len = fread(buffer, sizeof(uint8_t), BUFFSIZE, file))) {
		state.length += b_len;
		sha256(&state, buffer, b_len);
        memset(buffer, 0x00, BUFFSIZE);
	}
    sha256Finalise(&state);

	return 0;
}
