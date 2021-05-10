// I only use strings.h for strcmp. Maybe I can flex and not use it.
#include <string.h>

#include "core.h"

struct Command commandInfo(struct Lang *core, char *first) {
	for (int c = 0; c < core->commands; c++) {
		if (!strcmp(first, core->command[c].first)) {
			return core->command[c];
		}
	}

	return core->command[0];
}

// Get int for when string starts (or not starts,
// then it will be -1.)
int handleFirst(struct Lang *core, struct Tree *tree) {
	if (tree->partsLength == 0) {
		struct Command info = commandInfo(
			core,
			tree->parts[tree->partsLength].value
		);

		return info.start;
	}

	return -1;
}

// Corescript parsing algorithm
struct Tree parse(struct Lang *core, char *command) {
	struct Tree tree;
	tree.ignoreType = '\0';

	int commandStarted = 0;
	int stringStarted = 0;
	int startString = -1; // When to start string, -1 for less than 0
	int addThis = 0;
	int appendX = 0; // Appending int for strings

	tree.indent = 0;
	tree.stringsLength = 0;
	tree.partsLength = 0;
	for (int c = 0; command[c] != '\0'; c++) {
		tree.strings[tree.stringsLength].type = 0;
		
		// Don't start yet if indented
		if (commandStarted == 0) {
			if (command[c] == INDENT_CHAR) {
				tree.indent++;

				// Ignore lines with just indents
				if (command[c + 1] == '\0') {
					tree.ignore = 1;
					return tree;
				}

				continue;
			} else {
				commandStarted = 1;

				// After indent (or not), check for ignored things,
				// Labels are parsed into a part, comments and newlines
				// are exited on detection (return tree).
				tree.ignore = 1;
				switch (command[c]) {
				case COMMENT:
					tree.ignoreType = COMMENT;
					return tree;
				case LABEL:
					// With labels, skip the ':' and naturally go
					// on adding a part. It won't go to string unless there is a
					// space in the label
					tree.ignoreType = LABEL;
					c++;
					break;
				case '\0':
					// blank line
					return tree;
				default:
					tree.ignore = 0;
				}
			}
		}

		// Check if we reached the string yet and
		// set default type to zero
		if (tree.partsLength == startString) {
			stringStarted = 1;
		}

		if (stringStarted) {
			if (command[c] == RAW_START) {
				// Skip when already on sperate part (first char)
				if (appendX == 0) {
					continue;
				}

				addThis = 1;
			} else if (command[c] == RAW_END) {
				tree.strings[tree.stringsLength].type = RAW;
				addThis = 1;
			}

			if (tree.strings[tree.stringsLength].type != RAW) {
				tree.strings[tree.stringsLength].type = STRING;
			}
		} else {
			if (command[c] == PART_SPLIT) {
				addThis = NEWNOCHAR;
			}
		}

		// Append when on last char
		if (command[c + 1] == '\0' && addThis == DONTADD) {
			addThis = NEWYESCHAR;

			// Set first part initial value
			// It is set to string, but will change later if RAW
			tree.strings[tree.stringsLength].type = STRING;
		}

		// Append char (unless told not to)
		if (addThis != NEWNOCHAR) {
			if (stringStarted) {
				tree.strings[tree.stringsLength].value[appendX] = command[c];
			} else {
				tree.parts[tree.partsLength].value[appendX] = command[c];
			}

			appendX++;
		}

		// Increment to the next string (string or regular part)
		if (addThis != 0) {
			if (stringStarted) {
				tree.strings[tree.stringsLength].value[appendX] = '\0';
				tree.stringsLength++;

				// Set default value (not for when stringlengths is 1)
				tree.strings[tree.stringsLength].type = STRING;
			} else {
				tree.parts[tree.partsLength].value[appendX] = '\0';

				// Handle when string starts (or if there is string)
				// once we are adding the first part
				// Also, core can be passed as null too.
				if (tree.partsLength == 0 && core != NULL) {
					startString = handleFirst(core, &tree);
				}

				tree.partsLength++;
			}

			appendX = 0;
		}

		// Reset for next char test
		addThis = DONTADD;
	}

	return tree;
}

// A very simple function parser. (Just splits by spaces)
struct Function parseFunction(char *string, int length) {
	struct Function function;
	int partC = 0;
	function.partsLength = 0;
	function.lengths[0] = 0;
	for (int c = 0; c < length; c++) {
		if (string[c] == ' ') {
			function.parts[function.partsLength][partC] = '\0';

			function.partsLength++;
			function.lengths[function.partsLength] = 0;
			partC = 0;

			continue;
		}

		function.parts[function.partsLength][partC] = string[c];
		function.lengths[function.partsLength]++;
		partC++;
	}

	// Null terminate last part since it does not end with ' '
	function.parts[function.partsLength][partC] = '\0';

	return function;
}
