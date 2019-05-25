#ifndef GBROM_H
#define GBROM_H
#include <stdint.h>
#include <stdbool.h>

#define GBROM_HEADER_START 0x100
#define GBROM_NINTENDO_LOGO_START 0x104
#define GBROM_NINTENDO_LOGO_SIZE 0x30
#define GBROM_CGB_FLAG_START 0x143
#define GBROM_NEW_LICENSE_CODE_START 0x144
#define GBROM_SGB_FLAG_START 0x146
#define GBROM_RAM_SIZE_START 0x149
#define GBROM_DEST_CODE_START 0x14a

#define GBROM_NEW_LICENSE_CODE_MAX 0xA4

static const uint8_t GBROM_NINTENDO_LOGO[GBROM_NINTENDO_LOGO_SIZE] = {
	0xce, 0xed, 0x66, 0x66, 0xcc, 0x0d, 0x00, 0x0b, 0x03, 0x73, 0x00, 0x83, 
	0x00, 0x0c, 0x00, 0x0d, 0x00, 0x08, 0x11, 0x1f, 0x88, 0x89, 0x00, 0x0e, 
	0xdc, 0xcc, 0x6e, 0xe6, 0xdd, 0xdd, 0xd9, 0x99, 0xbb, 0xbb, 0x67, 0x63, 
	0x6e, 0x0e, 0xec, 0xcc, 0xdd, 0xdc, 0x99, 0x9f, 0xbb, 0xb9, 0x33, 0x3e
};

struct gbrom {
	uint8_t entry_point[4];
	uint8_t logo[48];
	uint8_t title[11];
	uint8_t manufacturer_code[4];
	uint8_t cgb_flag;
	uint8_t license_code[2];
	uint8_t sgb_flag;
	uint8_t cartridge_type;
	uint8_t rom_size;
	uint8_t ram_size;
	uint8_t dest_code;
	uint8_t old_license_code;
	uint8_t version_number;
	uint8_t header_checksum;
	uint8_t global_checksum[2];
};

struct gbrom gbrom_read(const char *input_fp);
bool gbrom_validate(const struct gbrom *rom);
void gbrom_print(const struct gbrom *rom);

#endif