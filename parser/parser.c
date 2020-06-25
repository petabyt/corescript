#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../struct.h"

struct Core core[COMMANDS] = {
	{"print", 2},
	{"var", 4},
	{"input", 4},
	{"goto", 1},
	{"if", 4},
	{"set", 4},
	{"return", 1}
};


int getMin(char string[]) {
	for (size_t i = 0; i < COMMANDS; i++) {
		if (strcmp(string, core[i].first) == 0) {
			return core[i].min;
		}
	}

	return -1;
}

// The classic Corescript style command parser
void parse(struct Memory *memory, struct Command *command, char *code, int l) {
	command -> ignore = 0;

	// Skip if comment or label
	if (code[0] == '#') {
		command -> ignore = 1;
		return;
	}

	if (code[0] == ':') {
		strcpy(memory -> labels[memory -> labelsAdded].name, code + 1);
		memory->labels[memory->labelsAdded].line = l;
		memory->labelsAdded++;

		command -> ignore = 1;
		return;
	}

	if (code[0] == '\n' || code[0] == '\n') {
		command -> ignore = 1;
		return;
	}

	int lineLength = strlen(code);
	char reading[lineLength];
	memset(reading, '\0', lineLength);

	// Markers for the core command parser
	int readingChar = 0;
	int addPart = 0;
	int partsAdded = 0;

	// Some markers for the string parser
	int stringsAdded = 0;
	int stringType = 1;
	int stopAt = -1;
	int stringStarted = 0;

	for (size_t c = 0; c < lineLength; c++) {
		if (stringStarted == 0) {
			if (code[c] == ' ') {
				addPart = 1;
			}
		} else {
			if (code[c] == '(') {
				addPart = 1;

				// Add before string
				stringType = 1;
			} else if (code[c] == ')') {
				addPart = 1;

				// Add thing in parenthesis
				stringType = 0;
			}
		}

		// If not already decided, add part if on last char
		if (c + 1 == lineLength && addPart == 0) {
			addPart = 2;
		}

		// Add the next char unless told not to
		if (addPart != 1) {
			reading[readingChar] = code[c];
			readingChar++;
		}

		// Append to the strings or parts array
		if (addPart != 0) {
			// Determine where to start once we
			// have first item in
			if (partsAdded == 0) {
				stopAt = getMin(reading);
			}

			// Append to different arrays (strings/parts)
			if (stringStarted == 0) {
				if (partsAdded == stopAt - 2) {
					stringStarted = 1;
				}

				strcpy(command -> parts[partsAdded], reading);
				partsAdded++;
			} else {
				strcpy(command -> strings[stringsAdded].string, reading);
				command -> strings[stringsAdded].type = stringType;

				stringsAdded++;
				stringType = 1;
			}

			memset(reading, '\0', lineLength);
			readingChar = 0;
			addPart = 0;
		}
	}

	command -> stringsAdded = stringsAdded;
}
