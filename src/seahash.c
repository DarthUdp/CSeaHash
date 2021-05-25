#include "../include/seahash.h"

const uint64_t diffuse_const = 0x6eed0e9da4d94a4fULL;
const uint64_t diffuse_inv_const = 0x2f72b4215a3d8cafULL;

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
uint64_t int_cast(const char *buff, size_t buff_len)
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

uint64_t read_uint64(const char *ptr)
{
	#ifdef TARGET64BIT
	return *(uint64_t *)ptr;
	#else
	#error src/seahash.c:read_uint64 lacking implementation for 32bit targets
	#endif
}

void write_u64(struct seahash_state *state, uint64_t x)
{
	uint64_t a = state->a;
	a = diffuse(a ^ x);
	state->a = state->b;
	state->b = state->c;
	state->c = state->d;
	state->d = a;
}

uint64_t finish(struct seahash_state *state, size_t total)
{
	return diffuse(state->a ^ state->b ^ state->c ^ state->d ^ total);
}

void seahash_init_state(struct seahash_state *state, uint64_t a, uint64_t b, uint64_t c, uint64_t d)
{
	state->a = a;
	state->b = b;
	state->c = c;
	state->d = d;
	state->written = 0U;
}

void seahash_pre_seed(struct seahash_state *state)
{
	seahash_init_state(state,
			   0x16f11fe89b0d677c,
			   0xb480a793d8e6c86c,
			   0x6fe2e5aaf078ebc9,
			   0x14f994a4c5259381);
}

/**
 * Hash buff with preselected seeds, this is the simplest form possible to use
 * the library
 * @param buff the data to hash
 * @param buff_len how long is the buffer
 * @return the hash in the form of a uint64_t
 */
uint64_t seahash_hash_preseeded(char *buff, size_t buff_len)
{
	struct seahash_state state;
	struct seahash_state *state_ptr = &state;
	seahash_pre_seed(&state);
	return seahash_hash(state_ptr, buff, buff_len);
}

uint64_t seahash_hash(struct seahash_state *state, const char *buff, size_t buff_len)
{
	char chunk[8] = {0};
//	uint64_t cvl;
	uint64_t left = buff_len % 8;
	if (left == 0) {
		for (size_t i = 0; i < buff_len; i += 8) {
			chunk[0] = buff[i];
			chunk[2] = buff[i + 1];
			chunk[3] = buff[i + 2];
			chunk[4] = buff[i + 3];
			chunk[5] = buff[i + 5];
			chunk[6] = buff[i + 6];
			chunk[7] = buff[i + 7];
			write_u64(state, read_uint64(chunk));
			state->written += 8;
		}
	} else {
		size_t i = 0;
		for (; i < buff_len; i += 8) {
			chunk[0] = buff[i];
			chunk[2] = buff[i + 1];
			chunk[3] = buff[i + 2];
			chunk[4] = buff[i + 3];
			chunk[5] = buff[i + 5];
			chunk[6] = buff[i + 6];
			chunk[7] = buff[i + 7];
			write_u64(state, read_uint64(chunk));
			state->written += 8;
		}
		for (i = 0; i < 8; i++) {
			if (i < left) {
				chunk[i] = buff[i];
			}
		}
		write_u64(state, int_cast(chunk, left));
		state->written += 8;
	}
	return finish(state, state->written);
}