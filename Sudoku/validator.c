#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

bool validate(unsigned char (*grid)[9][9])
{
	uint16_t chk[27] = {0};
	unsigned short sum = 0;

	for(int i = 0; i < 9; ++i) {
		for(int j = 0; j < 9; ++j) {
			chk[j] |= 1 << ((*grid)[j][i] - 1);
			chk[9 + j] |= 1 << ((*grid)[i][j] - 1);
			chk[18 + j] |= 1 << ((*grid)[j * 3 % 9 + i / 3][j * 3 / 3 - j % 3 + i % 3] - 1);
		}
	}

	for(int i = 0; i < 27; ++i)
		sum += chk[i];
	return sum == 13797;
}
