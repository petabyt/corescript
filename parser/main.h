// Parsing runtime enum
enum Parser {
	ADD_NEXT = 2,
	RAW = 1,
	STRING = 2
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
