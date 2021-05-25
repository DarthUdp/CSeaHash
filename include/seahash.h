#ifndef SEAHASH_LIBRARY_H
#define SEAHASH_LIBRARY_H

#include <stddef.h>
#include <stdint.h>

struct seahash_state;

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
extern uint64_t seahash_hash_preseeded(char *buff, size_t buff_len);
extern uint64_t seahash_hash(struct seahash_state *state, const char *buff, size_t buff_len);

#endif //SEAHASH_LIBRARY_H
