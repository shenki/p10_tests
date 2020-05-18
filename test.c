#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/auxv.h>

extern void test_prefix(void);
extern int test_mma(uint16_t (*)[8], uint16_t (*)[8], uint32_t (*)[4*4]);

static void mma(void) {
	int i;
	uint16_t x[] = {1, 0, 2, 0, 3, 0, 4, 0};
	uint16_t y[] = {1, 0, 2, 0, 3, 0, 4, 0};
	uint32_t z[4*4];

	printf("Smoke test MMA\n");
	test_mma(&x, &y, &z);

	for(i = 0; i < 16; i++)
		printf("MMA[%d] = %d\n", i, z[i]);
}

static void prefix(void) {
	printf("Smoke test prefix\n");
	test_prefix();
}

static void hwcap(void) {
	unsigned long at_hwcap = getauxval(AT_HWCAP);
	unsigned long at_hwcap2 = getauxval(AT_HWCAP2);

	printf("HWCAP: 0x%08lx HWCAP2: 0x%08lx\n", at_hwcap, at_hwcap2);
	printf("ISAv3.1: %s\n", at_hwcap2 & 0x00040000 ? "Yes" : "No");
	printf("MMA: %s\n", at_hwcap2 & 0x00040000 ? "Yes" : "No");
}

int main(int argc, char *argv[]) {
	char opt;

	while ((opt = getopt(argc, argv, "mpl")) != 255) {
		switch (opt) {
		case 'm':
			mma();
			break;
		case 'p':
			prefix();
			break;
		case 'c':
			hwcap();
			break;
		default:
			fprintf(stderr, "Unknown option %c\n", opt);
			fprintf(stderr, "Usage: %s [-m] [-p]\n", argv[0]);
			fprintf(stderr, "\t-p: smoke test prefix\n");
			fprintf(stderr, "\t-m: smoke test mma\n");
			exit(-1);
			break;
		}
	}

	return 0;
}
