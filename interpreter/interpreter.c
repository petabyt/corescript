#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../struct.h"
#include "../parser/parser.h"

// A function to return the location of a variable
int findVariable(struct Memory memory, char *name) {
	for (int i = 0; i < memory.variablesAdded; i++) {
		if (strcmp(memory.variables[i].name, name) == 0) {
			return i;
		}
	}

	return -1;
}

void setVariable(struct Memory *memory, char *name, char *string) {
	int find = findVariable(*memory, name);

	if (find == -1) {
		strcpy(memory -> variables[memory -> variablesAdded].name, name);
		strcpy(memory -> variables[memory -> variablesAdded].value, string);
		memory -> variablesAdded++;
	} else {
		memset(memory -> variables[find].value, '\0', 20);
		strcpy(memory -> variables[find].value, string);
	}
}

int tryInt(int *result, char *string) {
	char *temp;
	*result = strtol(string, &temp, 10);
	if (*temp != '\0') {
		return -1;
	}

	return 1;
}

// Check integer, check if variable,
// check if variable value.
int tryIntOrVariable(struct Memory memory, int *result, char *string) {
	int try = tryInt(result, string);
	if (try == -1) {
		int tryFindVariable = findVariable(memory, string);
		if (tryFindVariable != -1) {
			int variable = 0;
			int tryVariable = tryInt(
				&variable,
				memory.variables[tryFindVariable].value
			);

			if (tryVariable != -1) {
				*result = variable;
			}

			return 1;
		}
	}

	return 1;
}

// A function to return the location of a label
int findLabel(struct Memory memory, char *string) {
	for (int i = 0; i < memory.labelsAdded; i++) {
		if (strcmp(memory.labels[i].name, string) == 0) {
			return i;
		}
	}

	return -1;
}

// Note than when goto/return commands are used, they are
// sent back to the label itself rather than the next line.
// But since it is used only in for loops, the line number
// will be increased before hitting the next line, so they
// cancel out.
int gotoLabel(struct Memory memory, char *label, int l) {
	int labelLocation = findLabel(memory, label);
	memory.labels[labelLocation].lastUsed = l;
	
	return memory.labels[labelLocation].line;
}

int gotoLabelLastUsed(struct Memory memory, char *label, int l) {
	int labelLocation = findLabel(memory, label);
	
	return memory.labels[labelLocation].lastUsed;
}

// Get contents between the colon, for "if"
void afterColon(char *whole, char *after) {
	int length = strlen(whole);
	int lastColon = 0;
	for (int i = length; i > 0; i--) {
		if (whole[i] == ':') {
			lastColon = i;
			break;
		}
	}

	int afterChar = 0;
	whole[lastColon] = '\0';
	for (int c = lastColon + 1; c < length; c++) {
		after[afterChar] = whole[c];
		afterChar++;

		whole[c] = '\0';
	}
}

// Simple mathematical parser
// TODO: implement "char" in this
int doCalculation(struct Memory memory, int *result, char parts[20][20]) {
	if (strcmp(parts[0], "len") == 0) {
		int tryVariable = findVariable(memory, parts[1]);
		if (tryVariable == -1) {
			return -1;
		}

		*result = strlen(memory.variables[tryVariable].value);
		return 1;
	}
	
	// Else, proceed to parse as variable, int..
	int min = 0;
	int tryMin = tryIntOrVariable(memory, &min, parts[1]);
	if (tryMin == -1) {
		*result = -1;
		return 1;
	}

	int max = 0;
	int tryMax = tryIntOrVariable(memory, &max, parts[2]);
	if (tryMax == -1) {
		*result = -1;
		return 1;
	}

	if (strcmp(parts[0], "add") == 0) {
		*result =  min + max;
	} else if (strcmp(parts[0], "sub") == 0) {
		*result =  min - max;
	} else if (strcmp(parts[0], "mult") == 0) {
		*result =  min * max;
	} else if (strcmp(parts[0], "div") == 0) {
		*result =  min / max;
	} else if (strcmp(parts[0], "lesser") == 0) {
		if (min < max) {
			*result =  1;
		} else {
			*result = -1;
		}
	} else if (strcmp(parts[0], "greater") == 0) {
		if (min > max) {
			return 1;
		} else {
			return -1;
		}
	} else {
		return -1;
	}

	return 1;
}
