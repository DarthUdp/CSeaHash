#include <seahash.h>
#include <string.h>
#include <stdio.h>

uint64_t hash_file(const char *fname)
{
	struct seahash_state state;
	char buff[128] = { 0 };
	uint64_t accum = 0;
	FILE *fp = fopen(fname, "r");
	if (fp == NULL)
		return -1;
	seahash_pre_seed(&state);
	fseek(fp, 0L, SEEK_END);
	size_t sz = ftell(fp);
	rewind(fp);

	for (size_t i = 0; i < sz; i += 128) {
		fread(&buff, 32, 4, fp);
		accum ^= seahash_hash(&state, buff, 128);
	}
	fclose(fp);
	return accum;
}

int main(int argc, char **argv)
{
	if (argc < 1)
		return -1;
	else if (strcmp(argv[1], "-f") == 0)
		printf("%lX\n", hash_file(argv[2]));
	else
		printf("%lX\n", seahash_hash_preseeded(argv[1], strlen(argv[1])));
	return 0;
}
