#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "rom.h"

struct gbrom gbrom_read(const char *input_fp)
{
	struct gbrom rom;

	FILE *fh = fopen(input_fp, "rb");
	if (! fh) {
		printf("Error: %s either doesn't exist, couldn't be read, or is zero " \
			"bytes.\n",
			input_fp);
		exit(1);
	}
	
	fseek(fh, GBROM_HEADER_START, SEEK_SET);
	fread(&rom, sizeof(struct gbrom), 0x1, fh);
	fclose(fh);

	return rom;
}

bool gbrom_validate(const struct gbrom *rom)
{
	// Validate the logo bytes.
	for (int i=0; i<GBROM_NINTENDO_LOGO_SIZE; ++i) {
		if (rom->logo[i] != GBROM_NINTENDO_LOGO[i]) {
			printf("Expected byte 0x%02X but got 0x%02X at 0x%04X in logo " \
				"data.\n", GBROM_NINTENDO_LOGO[i], rom->logo[i], 
				GBROM_NINTENDO_LOGO_START + i + 1);
			return false;
		}
	}

	if (rom->license_code[0] > 99) {
		printf("Expected a license code less than 0x%02X but got 0x%02X at " \
			"0x%04X.\n", GBROM_NEW_LICENSE_CODE_MAX, rom->license_code[0], 
			GBROM_NEW_LICENSE_CODE_START);
	}

	if (rom->sgb_flag != 0x00 && rom->sgb_flag != 0x3) {
		printf("Expected SGB byte of either 0x00 or 0x3 but got 0x%02X at " \
			"0x%04X.\n", rom->sgb_flag, GBROM_SGB_FLAG_START);
	}

	if (rom->ram_size > 0x5) {
		printf("Expected ram size byte less than 0x05 but got 0x%02X at " \
			"0x%04X.\n", rom->ram_size, GBROM_RAM_SIZE_START);
	}

	if (rom->dest_code > 0x1) {
		printf("Expected destination byte less than 0x01 but got 0x%02X at " \
			"0x%04X.\n", rom->dest_code, GBROM_DEST_CODE_START);
	}

	// Do checksums here.

	/*
	Debug: for dumping bytes from struct...
	for (int i=0; i<sizeof(struct gbrom); ++i) {
		printf("%02X ", *((uint8_t *)rom + i));
	}
	printf("\n");
	*/

	return true;
}

void gbrom_print(const struct gbrom *rom)
{
	uint8_t safe_title[16] = {0};
	memcpy(safe_title, rom->title, 11);

	printf("Title: %s\n", safe_title);
	printf("Color support? %s\n", (rom->cgb_flag & 0x8) ? "Yes" : "No");
	printf("SGB supported: %s\n", 
		rom->sgb_flag == 0x3 ? "Yes" : "No");
}