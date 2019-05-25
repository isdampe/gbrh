#include <stdio.h>
#include "rom.h"

int main(const int argc, const char **argv)
{
	if (argc < 2) {
		printf("Usage: cpgh input.rom\n");
		return 1;
	}

	struct gbrom rom = gbrom_read(argv[1]);
	if (! gbrom_validate(&rom)) {
		printf("Error: %s is not a valid gb ROM.\n", argv[1]);
		return 1;
	}

	gbrom_print(&rom);
	return 0;
}