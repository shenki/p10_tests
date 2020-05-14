/* Load an immediate 64-bit value into a register */
#define LOAD_IMM64(r, e)                        \
        lis     r,(e)@highest;                  \
        ori     r,r,(e)@higher;                 \
        rldicr  r,r, 32, 31;                    \
        oris    r,r, (e)@high;			\
        ori     r,r, (e)@l;

	.global test_prefix
test_prefix:
	/* Prefixed instruction (dnop) */
	.long 0x07000000
	.long 0x00000000
	blr

	.global test_mma
test_mma:
	/* Load accumulator via VSX registers from image passed in r3 */
	lxvh8x	4,0,3
	lxvh8x	5,0,4

	/* Clear and prime the accumulator (xxsetaccz) */
	.long	0x7c030162

	/* Prime the accumulator with MMA VSX move to accumulator
	* X-form (xxmtacc) (not needed due to above zeroing) */
	//.long 0x7c010162

	/* xvi16ger2s */
	.long	0xec042958

	/* Store result in image passed in r5 */
	stxvw4x	0,0,5
	addi	5,5,16
	stxvw4x	1,0,5
	addi	5,5,16
	stxvw4x	2,0,5
	addi	5,5,16
	stxvw4x	3,0,5
	addi	5,5,16

	blr
