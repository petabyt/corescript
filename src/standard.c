#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "core.h"

// TODO: Improve error messages

// Parse Corescript standard functions
int standard(struct Memory *memory, struct Lang *core, struct Tree *tree, int line) {
	// Make a simple pointer to the first part
	char *first = tree->parts[0].value;

	char string[MAX_STRING] = {0};
	if (!strcmp(first, core->command[0].first)) {
		// print
		parseString(string, tree, memory);
		puts(string);
	} else if (!strcmp(first, core->command[1].first)) {
		// var
		parseString(string, tree, memory);
		createVariable(
			tree->parts[1].value,
			string,
			memory
		);
	} else if (!strcmp(first, core->command[2].first)) {
		// set
		parseString(string, tree, memory);
		setVariable(
			tree->parts[1].value,
			string,
			memory
		);
	} else if (!strcmp(first, core->command[3].first)) {
		// goto
		parseString(string, tree, memory);

		// Subtract one because the loop will move ahead
		// after setting
		int tryLabel = gotoLabel(
			string,
			line,
			memory
		);

		if (tryLabel == -1) {
			printf("%s%d%s\n", "Line ", line + 1, ": Label not found");
			return tryLabel;
		} else {
			line = tryLabel;
		}
	} else if (!strcmp(first, core->command[4].first)) {
		// if
		parseString(string, tree, memory);

		int error = 0;
		int tryLine = testCondition(
			&error,
			tree->parts[2].value,
			tree->parts[1].value,
			string,
			line,
			memory
		);

		// Exit if error is -5, which means it is false,
		// not really an error.
		if (error == FALSE) {
			return line;
		}

		if (error != 0) {
			printf("%d %s%d\n", line + 1, "Error parsing condition: ", error);
			return error;
		} else {
			// Subtract one because the loop will move ahead
			// after setting, same did with goto
			line = tryLine;
		}
	} else if (!strcmp(first, core->command[5].first)) {
		// return
		parseString(string, tree, memory);

		int tryLabel = findLabel(
			string,
			memory
		);

		if (tryLabel == -1) {
			printf("%s%d\n", "Label not Found: ", tryLabel);
			return tryLabel;
		} else {
			line = memory->labels[tryLabel].lastUsed;
		}
	}

	return line;
}
