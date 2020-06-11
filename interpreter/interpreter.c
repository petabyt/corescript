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

int gotoLabel(struct Memory memory, char *label, int l, int type) {
	int labelLocation = findLabel(memory, label);
	memory.labels[labelLocation].lastUsed = l;

	int toGoto;
	if (type == 0) {
		toGoto = memory.labels[labelLocation].line;
	} else {
		toGoto = memory.labels[labelLocation].lastUsed;
	}

	l = toGoto;
}

// Get contents between the colon
// Just for IF
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

// Corescript calculation parser
int doCalculation(struct Memory memory, int *result, char p1[], char p2[], char p3[]) {
	if (strcmp(p1, "len") == 0) {
		int tryVariable = findVariable(memory, p2);
		if (tryVariable == -1) {
			return -1;
		}

		*result = strlen(memory.variables[tryVariable].value);
		return 1;
	}

	int min = 0;
	int tryMin = tryIntOrVariable(memory, &min, p2);
	if (tryMin == -1) {
		*result = -1;
		return 1;
	}

	int max = 0;
	int tryMax = tryIntOrVariable(memory, &max, p3);
	if (tryMax == -1) {
		*result = -1;
		return 1;
	}

	if (strcmp(p1, "add") == 0) {
		*result =  min + max;
	} else if (strcmp(p1, "sub") == 0) {
		*result =  min - max;
	} else if (strcmp(p1, "mult") == 0) {
		*result =  min * max;
	} else if (strcmp(p1, "div") == 0) {
		*result =  min / max;
	} else if (strcmp(p1, "lesser") == 0) {
		if (min < max) {
			*result =  1;
		} else {
			*result = -1;
		}
	} else if (strcmp(p1, "greater") == 0) {
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
