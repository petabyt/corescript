#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../parser/main.h"
#include "../parser/parser.h"
#include "../math/math.h"
#include "../runtime/runtime.h"

// TODO: seperate into functions Ex standard_print, standard_goto...
int standard(struct Memory *memory, struct Lang *core, struct Tree *tree, int line) {
	// Make a simple pointer to the first part
	void *first = tree->parts[0].value;

	if (!strcmp(first, core->command[0].first)) {
		// print
		char string[50];
		memset(string, '\0', 50);
		parseString(string, tree, memory);

		puts(string);
	} else if (!strcmp(first, core->command[1].first)) {
		// var
		char string[50];
		memset(string, '\0', 50);
		parseString(string, tree, memory);

		createVariable(
			tree->parts[1].value,
			string,
			memory
		);
	} else if (!strcmp(first, core->command[2].first)) {
		// set
		char string[50];
		memset(string, '\0', 50);
		parseString(string, tree, memory);

		setVariable(
			tree->parts[1].value,
			string,
			memory
		);
	} else if (!strcmp(first, core->command[3].first)) {
		// goto
		char string[50];
		memset(string, '\0', 50);
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
	} else if (!strcmp(first, core->command[4].first)) { // IF
		char string[50];
		memset(string, '\0', 50);
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
		if (error == -5) {
			return line;
		}

		if (error != 0) {
			printf("%d %s%d\n", (line + 1), "Error parsing condition: ", error);
			return error;
		} else {
			// Subtract one because the loop will move ahead
			// after setting, same did with goto
			line = tryLine;
		}
	} else if (!strcmp(first, core->command[5].first)) { // RETURN
		char string[50];
		memset(string, '\0', 50);
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
