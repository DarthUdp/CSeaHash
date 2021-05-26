#include <ctest.h>
#include <stdio.h>
#include <seahash.h>
#include <string.h>
#include <malloc.h>

void test_all_words()
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	uint64_t hash;
	FILE *fp = fopen("../test/words.txt", "r");
	while ((read = getline(&line, &len, fp)) != -1) {
		hash = seahash_hash_preseeded(line, read);
		line[strlen(line) - 1] = ' ';
		printf("%s %lX\n", line, hash);
	}
	fclose(fp);
	if (line)
		free(line);
}

void test_numbers()
{
	for (uint64_t i = 0; i < 216553; i++) {
		printf("%lu %lX\n", i, seahash_hash_preseeded((const char *)&i, 4));
	}
}

int main(int argc, char *argv[])
{
	test_all_words();
	test_numbers();
	return 0;
}
