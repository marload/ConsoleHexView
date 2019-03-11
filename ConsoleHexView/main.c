#include <stdio.h>
#include <stdlib.h>

char asciiToChar(char ascci) {
	if (ascci < 0x20)
		return 0x2E;
	else
		return ascci;
}

void view(const unsigned char* arr, long size) {
	long i = 0;
	int j = 0;
	printf("Offset(hex) 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F     decode viewer\n");
	for (i = 0; i < size; i += 0x10) {
		printf("   %08X ", i);
		for (j = 0; j <= 0x0F; ++j) {
			printf("%2X ", arr[i + j]);
		}
		for (j = 0; j <= 0x0F; j++) {
			printf("%c", asciiToChar(arr[i+j]));
		}
		printf("\n");
	}
}

int main(int argc, char** argv) {
	if (argc < 2) {
		fprintf(stderr, "[ERROR] Please Input file PATH\n");
		return EXIT_FAILURE;
	}

	const unsigned char* filename = argv[1];
	FILE *file = fopen(filename, "rb");
	long size = 0;

	if (file == NULL) {
		fprintf(stderr, "[ERROR] Failed to open file.\n");
		return EXIT_FAILURE;
	}

	fseek(file, 0, SEEK_END);
	size = ftell(file);
	rewind(file);

	char* data = (char*)malloc(sizeof(char)*size);
	if (fread(data, sizeof(char), size, file) < size) {
		fprintf(stderr, "[ERROR] Failed to read file");
		return exit;
	}

	view(data, size);
}