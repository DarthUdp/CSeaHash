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
 * Hash a buffer
 * @param state
 * @param buff
 * @param buff_len
 */
extern void seahash_hash(struct seahash_state *state, char *buff, size_t buff_len);

#endif //SEAHASH_LIBRARY_H
