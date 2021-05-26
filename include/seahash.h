/**
 * BSD 3-Clause License
 *
 * Copyright (c) 2021, Matheus Xavier
 * All rights reserved.
 * Find the code at: https://github.com/DarthUdp/CSeaHash
 */

#ifndef SEAHASH_LIBRARY_H
#define SEAHASH_LIBRARY_H

#include <stddef.h>
#include <stdint.h>

/*
 * Change these constants to define a different seed to use with seahash_hash_preseeded
 */
#define SEAHASH_PSEED_A 0x16f11fe89b0d677cUL
#define SEAHASH_PSEED_B 0xb480a793d8e6c86cUL
#define SEAHASH_PSEED_C 0x6fe2e5aaf078ebc9UL
#define SEAHASH_PSEED_D 0x14f994a4c5259381UL


struct seahash_state {
    uint64_t a;
    uint64_t b;
    uint64_t c;
    uint64_t d;
    uint64_t written;
};

/**
 * Initialize state with the provided a, b, c, d parameters
 * @param state seahash_state struct to initialize
 * @param a initial a seed
 * @param b initial b seed
 * @param c initial c seed
 * @param d initial d seed
 */
extern void seahash_init_state(struct seahash_state *state, uint64_t a, uint64_t b, uint64_t c, uint64_t d);
/**
 * Use preselected seeds for hashing, this is the recommended approach!
 * @param state a state to initialize
 */
extern void seahash_pre_seed(struct seahash_state *state);
/**
 * Hash buff with preselected seeds, this is the simplest form possible to use
 * the library
 * @param buff the data to hash
 * @param buff_len how long is the buffer
 * @return the hash in the form of a uint64_t
 */
extern uint64_t seahash_hash_preseeded(const char *buff, size_t buff_len);
/**
 * Hash using user provided seeds with state managed by the library code
 * @param buff
 * @param buff_len
 * @param a seed param a
 * @param b seed param b
 * @param c seed param c
 * @param d seed param d
 * @return the hash resulting from using the provided seeds
 */
extern uint64_t seahash_hash_seeded(const char *buff, size_t buff_len, uint64_t a, uint64_t b, uint64_t c, uint64_t d);
/**
 * hash using a user provided state, beware that this makes the final hashes depend on this state, can be used to hash
 * in chunks and streams
 * @param state
 * @param buff
 * @param buff_len
 * @return final hash
 */
extern uint64_t seahash_hash(struct seahash_state *state, const char *buff, size_t buff_len);

#endif //SEAHASH_LIBRARY_H
