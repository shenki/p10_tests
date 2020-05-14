CC = powerpc64le-linux-gnu-gcc
CFLAGS ?= -Wall

all: p10_tests.cpio

p10_tests.cpio: test
	find $< | cpio --quiet -H newc -o > p10_tests.cpio

test: test.c test.S
