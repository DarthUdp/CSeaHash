#include "../include/seahash.h"

const uint64_t diffuse_const = 0x6eed0e9da4d94a4fULL;
const uint64_t diffuse_inv_const = 0x2f72b4215a3d8cafULL;

/*
 * Helper functions */

/**
 * This is the function that provides chaos needed to build the hashing function
 */
uint64_t diffuse(uint64_t x)
{
	uint64_t a, b;
	x = x * diffuse_const;
	a = x >> 32;
	b = x >> 60;
	x ^= a >> b;
	x = x * diffuse_const;
	return x;
}

uint64_t undiffuse(uint64_t x)
{
	uint64_t a, b;
	x *= diffuse_inv_const;
	a = x >> 32;
	b = x >> 60;
	x ^= a >> b;
	x *= diffuse_inv_const;
	return x;
}

/*
 * makes a buffer where buff_len < 8 into a single uint64_t
 * !! if buff_len > 8 then ub
 */
uint64_t int_cast(char *buff, size_t buff_len)
{
	if (buff_len == 1) {
		// char
		return *(uint8_t *)buff;
	} else if (buff_len == 2) {
		// short
		return *(uint16_t *)buff;
	} else if (buff_len == 3) {
		// short + char
		uint16_t a = *(uint16_t *)buff;
		uint16_t b = *(uint8_t *)(buff + 2);
		return a | (b << 16);
	} else if (buff_len == 4) {
		// int
		return *(uint32_t *)buff;
	} else if (buff_len == 5) {
		// int + char
		uint32_t a = *(uint32_t *)buff;
		uint64_t b = *(uint8_t *)(buff + 4);
		return a | (b << 32);
	} else if (buff_len == 6) {
		// int + short
		uint32_t a = *(uint32_t *)buff;
		uint64_t b = *(uint16_t *)(buff + 4);
		return a | (b << 32);
	} else if (buff_len == 7) {
		// int + short + char
		uint32_t a = *(uint32_t *)buff;
		uint64_t b = *(uint16_t *)(buff + 4);
		uint64_t c = *(uint8_t *)(buff + 6);
		return a | (b << 32) | (c << 48);
	} else if (buff_len == 8) {
		// straight through
		return *(uint64_t *)buff;
	} else {
		// UB!
		return 0;
	}
}

uint64_t read_uint64()

/**
 * Describes the state of the algorithm
 */
struct seahash_state {
    uint64_t a;
    uint64_t b;
    uint64_t c;
    uint64_t d;
    uint64_t written;
};

void seahash_init_state(struct seahash_state *state, uint64_t a, uint64_t b, uint64_t c, uint64_t d)
{
	state->a = a;
	state->b = b;
	state->c = c;
	state->d = d;
	state->written = 0U;
}
