#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "parser/main.h"
#include "parser/parser.h"
#include "math/math.h"
#include "runtime/runtime.h"

// TODO: multiple files

enum Runtime {
	MAX_STRING_LENGTH = 50,
	MAX_LINE_LENGTH = 100,
	DELAY = 0
};

struct Error {
	char *VARIABLE_NOT_FOUND;
	char *COMMAND_NOT_FOUND;
}errorsa = {
	"Woah",
	"asd"
};

struct Lang core = {
	6,
	{
		{"print", 1},
		{"var", 3},
		{"set", 3},
		{"goto", 1},
		{"if", 3},
		{"return", 1}
	}
};

int main(int argc, char *argv[]) {
	if (argc == 1 || argv[1][0] == '?') {
		printf("%s\n", "Corescript Interpreter v0.1.1");
		return 0;
	}

	// Count file length
	FILE *file = fopen(argv[1], "r");
	char temp[MAX_LINE_LENGTH];
	int lineCount = 0;
	while (fgets(temp, MAX_LINE_LENGTH, file) != NULL) {
		lineCount++;
	}

	// Create str array with said line count
	char code[lineCount][MAX_LINE_LENGTH];

	// Store the
	FILE *file2 = fopen(argv[1], "r");
	char read[MAX_LINE_LENGTH];
	int line = 0;
	while (fgets(read, MAX_LINE_LENGTH, file2) != NULL) {
		strtok(read, "\n");
		strcpy(code[line], read);
		line++;
	}

	struct Memory memory;
	memory.variablesLength = 0;
	memory.labelsLength = 0;

	// Default variables
	createVariable("blank", "", &memory);
	createVariable("space", " ", &memory);

	// Look at all lines, but real line number is
	// excluding comments, labels
	int linesParsed = 0;

	// Test for things that won't be parsed
	struct Tree tree[lineCount];
	for (int l = 0; l < lineCount; l++) {
		tree[l] = parse(&core, code[l], strlen(code[l]));

		// Check if parser detected label. (it sends
		// it to the first part)
		if (tree[l].ignore && tree[l].ignoreType == ':') {
			memory.labels[memory.labelsLength].name = tree[l].parts[0].value;
			memory.labels[memory.labelsLength].line = l;
			memory.labelsLength++;
		}
	}

	for (int l = 0; l < lineCount; l++) {
		if (tree[l].ignore == 1) {
			continue;
		}

		// Optional delay between parsing commands
		usleep(DELAY);

		// Make a simple pointer to the first part
		// (just for it to loop better)
		void *first = &tree[l].parts[0].value;

		if (!strcmp(first, core.command[0].first)) {
			// print
			char string[50];
			memset(string, '\0', 50);
			parseString(string, &tree[l], &memory);

			printf("%s\n", string);
		} else if (!strcmp(first, core.command[1].first)) {
			// var
			char string[50];
			memset(string, '\0', 50);
			parseString(string, &tree[l], &memory);

			createVariable(
				tree[l].parts[1].value,
				string,
				&memory
			);
		} else if (!strcmp(first, core.command[2].first)) {
			// set
			char string[50];
			memset(string, '\0', 50);
			parseString(string, &tree[l], &memory);

			setVariable(
				tree[l].parts[1].value,
				string,
				&memory
			);
		} else if (!strcmp(first, core.command[3].first)) {
			// goto
			char string[50];
			memset(string, '\0', 50);
			parseString(string, &tree[l], &memory);

			// Subtract one because the loop will move ahead
			// after setting
			int tryLabel = gotoLabel(
				string,
				l,
				&memory
			);

			if (tryLabel == -1) {
				printf("%s%d%s\n", "Line ", l + 1, ": Label not found");
				return tryLabel;
			} else {
				//printf("_%d_%s\n", tryLabel - 1, code[l]);
				l = tryLabel;
			}
		} else if (!strcmp(first, core.command[4].first)) {
			// if
			char string[50];
			memset(string, '\0', 50);
			parseString(string, &tree[l], &memory);

			int error = 0;
			int line = testCondition(
				&error,
				tree[l].parts[2].value,
				tree[l].parts[1].value,
				string,
				l,
				&memory
			);

			// Exit if error is -5, which means it is false,
			// not really an error. There isn't much I can do without
			// making it more complicated, so here you go.
			if (error == -5) {
				continue;
			}

			if (error != 0) {
				printf("%d %s%d\n", (l + 1), "Error parsing condition: ", error);
				return error;
			} else {
				// Subtract one because the loop will move ahead
				// after setting, same did with goto
				l = line;
			}
		} else if (!strcmp(first, core.command[5].first)) { // RETURN
			char string[50];
			memset(string, '\0', 50);
			parseString(string, &tree[l], &memory);

			int tryLabel = findLabel(
				string,
				&memory
			);

			if (tryLabel == -1) {
				printf("%s%d\n", "Label not Found: ", tryLabel);
				return tryLabel;
			} else {
				l = memory.labels[tryLabel].lastUsed;
			}
		}
	}
}
