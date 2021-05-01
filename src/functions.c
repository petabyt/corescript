#include <string.h>

#include "core.h"

enum FuncErr {
	ERROR = -1
};

// A simple struct for testing different functions
struct TestFunction {
	int add; int sub; int char_; int len;
};

// Very basic function interpreter
int executeFunction(char *result, char *string, struct Memory *memory) {
	struct Function function = parseFunction(string, strlen(string));

	struct TestFunction testFunction;
	testFunction.add = !strcmp(function.parts[0], "add");
	testFunction.sub = !strcmp(function.parts[0], "sub");
	testFunction.char_ = !strcmp(function.parts[0], "char");
	testFunction.len = !strcmp(function.parts[0], "len");

	if (testFunction.sub || testFunction.add) {
		// Parse both numbers into
		// variable -> int
		// int
		// or else, error.

		int firstError = 0;
		int first = parseIntOrVar(&firstError, function.parts[1], function.lengths[1], memory);
		if (firstError) {
			return -3;
		}

		int secondError = 0;
		int second = parseIntOrVar(&secondError, function.parts[2], function.lengths[2], memory);
		if (secondError) {
			return -3;
		}

		if (testFunction.add) {
			intToStr(result, first + second);
		} else if (testFunction.sub) {
			intToStr(result, first - second);
		}

		return 0;
	} else if (testFunction.char_) {
		int tryVar = getVariable(function.parts[1], memory);
		if (tryVar == -1) {
		   return -2;
		}

		int intError = 0;
		int second = parseIntOrVar(&intError, function.parts[2], function.lengths[2], memory);
		if (intError) {
			return -3;
		}

		// Test if char of larger than string
		if (second > (int)strlen(memory->variables[tryVar].value)) {
			return -4;
		}

		result[0] = memory->variables[tryVar].value[second];
		return 0;
    } else if (testFunction.len) {
		int tryVar = getVariable(function.parts[1], memory);
		if (tryVar == -1) {
		   return -2;
		}

		intToStr(result, strlen(memory->variables[tryVar].value));
		return 0;
    }

	// Command not found
	return -1;
}
