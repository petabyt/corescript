#ifndef MAIN_H
#define MAIN_H

#define MAX_STRING 100

#define ADD_NEXT 2
#define RAW 1
#define STRING 2

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
		char name[50];
		char value[50];
		int length;
	}variables[20];
	int variablesLength;
	struct Labels {
		char name[50];
		int line;
		int lastUsed;
	}labels[10];
	int labelsLength;
};

// Corescript AST
struct Parts {
	char value[50];
};

struct Strings {
	int type;
	char value[50];
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
