#ifndef MAIN_H
#define MAIN_H

#define MAX_STRING 100

#define ADD_NEXT 2
#define RAW 1
#define STRING 2

enum Parser {
	DONTADD = 0, // Don't add
	NEWNOCHAR = 1, // New part and don't append current char
	NEWYESCHAR = 2 // New part and append current char
};

enum ConditionError {
	BAD_VAR = -1,
	NO_COLON = -2,
	BAD_LABEL = -3,
	INVALID_OPT = -4,
	FALSE = -5
};

enum Runtime {
	MAX_STRING_LENGTH = 128,
	MAX_LINE_LENGTH = 512
};

// Parser grammar configuration
enum Grammar {
	INDENT_CHAR = '\t',
	COMMENT = '#',
	LABEL = ':',
	RAW_START = '[',
	RAW_END = ']',
	PART_SPLIT = ' ',

	EQUAL = '=',
	GREATER = '>',
	LESSER = '<'
};

// Runtime memory
struct Memory {
	struct Variables {
		char name[128];
		char value[MAX_STRING];
		int length;
	}variables[50];
	int variablesLength;
	struct Labels {
		char name[128];
		int line;
		int lastUsed;
	}labels[50];
	int labelsLength;
};

// Corescript AST
struct Parts {
	char value[MAX_STRING];
};

struct Strings {
	int type;
	char value[MAX_STRING];
};

struct Tree {
	int ignore;
	char ignoreType;

	int indent;
	struct Parts parts[10];
	int partsLength;
	struct Strings strings[10];
	int stringsLength;
};

struct Function {
	int partsLength;
	char parts[5][20];
	int lengths[5];
};

// Main language
struct Lang {
	int commands;
	struct Command {
		char *first;
		int start;
	}command[];
};

// Store command names and expected args
static struct Lang english = {
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

int executeFunction(char *result, char *string, struct Memory *memory);
int standard(struct Memory *memory, struct Lang *core, struct Tree *tree, int line);

int getVariable(char *name, struct Memory *memory);
int setVariable(char *name, char *value, struct Memory *memory);
int createVariable(char *name, char *value, struct Memory *memory);
int parseIntOrVar(int *error, char *string, int length, struct Memory *memory);
int executeFunction(char *result, char *string, struct Memory *memory);
int parseRaw(char *buffer, char *string, struct Memory *memory);
void parseString(char *buffer, struct Tree *tree, struct Memory *memory);
int findLabel(char *name, struct Memory *memory);
int gotoLabel(char *name, int l, struct Memory *memory);
int testCondition(int *error, char *operator, char *first, char *second, char l, struct Memory *memory);

void intToStr(char *buffer, int num);
int strToInt(char *string, int *error, int length);

struct Tree parse(struct Lang *core, char *command);
struct Function parseFunction(char *string, int length);

#endif
