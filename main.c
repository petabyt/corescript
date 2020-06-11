#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "struct.h"
#include "parser/parser.h"
#include "interpreter/interpreter.h"

// String parser (very basic now)
void parseString(char *buffer, struct Command command, struct Memory memory) {
	for (size_t p = 0; p < command.stringsAdded; p++) {
		if (command.strings[p].type == 1) {
			strcat(buffer, command.strings[p].string);
		} else {
			int variable = findVariable(memory, command.strings[p].string);
			if (variable == -1) {
				struct Command function;
				parse(&memory, &function, command.strings[p].string, 0);

				int functionResult = 0;
				int tryFunction = doCalculation(
					memory,
					&functionResult,
					function.parts[0],
					function.parts[1],
					function.parts[2]
				);

				// TODO: this belongs in a functions function.
				if (tryFunction  == -1) {
					if (strcmp(function.parts[0], "char") == 0) {
						int tryVariable = findVariable(memory, function.parts[2]);
						if (tryVariable == -1) {
							break;
						}

						int max = 0;
						int tryMax = tryIntOrVariable(memory, &max, function.parts[1]);
						if (tryMax == -1) {
							break;
						}

						char character[1];
						character[0] = memory.variables[tryVariable].value[max];
						strcpy(buffer, character);
					}
				} else {
					char output[20];
					sprintf(output, "%d", functionResult);
					strcat(buffer, output);
				}

			} else {
				strcat(buffer, memory.variables[variable].value);
			}
		}
	}
}

int main() {

	// Create memory struct and add in
	// default variables
	struct Memory memory;
	memory.labelsAdded = 0;

	// TODO: better interface for this
	memory.variablesAdded = 2;
	strcpy(memory.variables[0].name, "blank");
	strcpy(memory.variables[0].value, "");
	strcpy(memory.variables[1].name, "space");
	strcpy(memory.variables[1].value, " ");

	// Initial tokenizer/parser
	// TODO: create command line application
	FILE *fileReader = fopen("example/hello.core", "r");
	char buffer[100];
	struct Command command[20];

	int lines = 0;
	while (fgets(buffer, 100, fileReader)) {
		strtok(buffer, "\n");
		parse(&memory, &command[lines], buffer, lines);
		lines++;
	}

	// The runner/executer is quite simple now
	// we have an AST of all the code.
	for (size_t l = 0; l < lines; l++) {
		if (command[l].ignore == 1) {
			continue;
		}

		if (strcmp(command[l].parts[0], "print") == 0) {
			char string[STRING_LENGTH] = "";
			parseString(string, command[l], memory);

			printf("%s\n", string);

		} else if (strcmp(command[l].parts[0], "var") == 0) {
			char string[STRING_LENGTH] = "";
			parseString(string, command[l], memory);

			setVariable(&memory, command[l].parts[1], string);

		}  else if (strcmp(command[l].parts[0], "set") == 0) {
			char string[STRING_LENGTH] = "";
			parseString(string, command[l], memory);

			setVariable(&memory, command[l].parts[1], string);

		} else if (strcmp(command[l].parts[0], "goto") == 0) {
			l = gotoLabel(memory, command[l].parts[1], l, 0);

		} else if (strcmp(command[l].parts[0], "return") == 0) {
			l = gotoLabel(memory, command[l].parts[1], l, 1);

		} else if (strcmp(command[l].parts[0], "input") == 0) {
			char string[STRING_LENGTH] = "";
			parseString(string, command[l], memory);

			printf("%s", string);
			char input[20];
			scanf("%s", input);

			setVariable(&memory, command[l].parts[1], input);

		} else if (strcmp(command[l].parts[0], "if") == 0) {
			char string[STRING_LENGTH] = "";
			parseString(string, command[l], memory);

			// Extract between string:label
			char label[STRING_LENGTH] = "";
			afterColon(string, label);

			// Test the different operators "=", ">", "<"
			int true = -1;
			int variable = findVariable(memory, command[l].parts[1]);
			if (command[l].parts[2][0] == '=') {
				if (strcmp(memory.variables[variable].value, string) == 0) {
					true = 1;
				}
			} else if (command[l].parts[2][0] == '>') {
				int result = 1;
				true = doCalculation(
					memory,
					&result,
					"greater",
					&memory.variables[variable].value[0],
					string
				);
			} else if (command[l].parts[2][0] == '<') {
				int result = 1;
				true = doCalculation(
					memory,
					&result,
					"lesser",
					&memory.variables[variable].value[0],
					string
				);
			}

			// Goto line if true
			if (true == 1) {
				l = gotoLabel(memory, label, l, 0);
			}

		} else {
			printf("Command error");
		}
	}

	return 0;
}
