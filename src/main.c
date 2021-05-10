#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "core.h"

void runCorescript(char **code, int lineCount) {
	struct Memory *memory = malloc(sizeof(struct Memory));
	memory->variablesLength = 0;
	memory->labelsLength = 0;

	// Default variables
	createVariable("blank", "", memory);
	createVariable("space", " ", memory);

	// Test for labels
	struct Tree tree;
	for (int l = 0; l < lineCount; l++) {
		tree = parse(
			&english,
			code[l]
		);

		// Store label if parser detected it
		if (tree.ignore && tree.ignoreType == ':') {
			strcpy(memory->labels[memory->labelsLength].name, tree.parts[0].value);
			memory->labels[memory->labelsLength].line = l;
			memory->labelsLength++;
		}
	}

	for (int l = 0; l < lineCount; l++) {
		tree = parse(
			&english,
			code[l]
		);

		if (tree.ignore) {
			continue;
		}

		// Parse command directly from "standard library"
		l = standard(
			memory,
			&english,
			&tree,
			l
		);
	}

	free(memory);
}
 
int main(int argc, char *argv[]) {
	if (argc == 1 || argv[1][0] == '?') {
		puts("Usage: corescript <file>");
		return 0;
	}

	// This pointer is used twice, and is reset for
	// the second reading
	FILE *file = fopen(argv[1], "r");
	if (file == NULL) {
		puts("File reading error.");
		return -1;
	}

	// Count file length
	char temp[MAX_LINE_LENGTH];
	int lineCount = 0;
	while (fgets(temp, MAX_LINE_LENGTH, file) != NULL) {
		lineCount++;
	}

	fseek(file, 0, SEEK_SET);

	// Allocate pointer to string array
	char **code = malloc(lineCount * sizeof(char **));

	// Store the program into the allocated array
	char read[MAX_LINE_LENGTH];
	int line = 0;
	while (fgets(read, MAX_LINE_LENGTH, file) != NULL) {
		code[line] = malloc(MAX_LINE_LENGTH * sizeof(char));
		strtok(read, "\n"); // remove trailing \n
		strcpy(code[line], read);
		line++;
	}

	fclose(file);
	
	runCorescript(code, lineCount);	

	for (int i = 0; i < line; i++) {
		free(code[i]);
	}

	free(code);
}
