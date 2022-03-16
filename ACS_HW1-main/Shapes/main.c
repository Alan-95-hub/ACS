#include "pch.h"
#include "container.h"

void usage() {
	printf("Usage: Shapes.exe <input_filename> <output_filename>\n");
	printf("       Shapes.exe -n <amount> <output_file>\n");
	printf("1 <= amount <= 10000\n");
}

int main(int argc, char** argv) {
	if (argc < 3) {
		printf("Incorrect amount of arguments.\n\n");
		usage();
		return -1;
	}

	FILE* input_file = NULL, * output_file = NULL;
	int amount = 0;

	if (!strcmp(argv[1], "-n")) {
		if (argc < 4) {
			printf("Incorrect amount of arguments.\n\n");
			usage();
			return -1;
		}
		amount = atoi(argv[2]);
		if (amount < 1 || amount > 10000) {
			usage();
			return -1;
		}
		output_file = fopen(argv[3], "w");
		if (!output_file) {
			printf("Error occured while opening file for writing\n");
			return -1;
		}
	}
	else {
		input_file = fopen(argv[1], "r");
		if (!input_file) {
			printf("Error occured while opening file for reading\n");
			return -1;
		}
		output_file = fopen(argv[2], "w");
		if (!output_file) {
			printf("Error occured while opening file for writing\n");
			return -1;
		}
	}
	

	Container* c = newContainer();
	if (input_file)
		inputContainer(c, input_file);
	else
		randomContainer(c, amount);

	outputContainer(c, output_file);
	outputStatistics(c, output_file);
	processContainer(c);
	outputContainer(c, output_file);

	clearContainer(c);
	return 0;
}