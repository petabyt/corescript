#define COMMANDS 7
#define STRING_LENGTH 50

struct StringPart {
	int type;
	char string[20];
};

struct Command {
	char parts[20][20];

	struct StringPart strings[5];
	int stringsAdded;

	int ignore;
};

struct Core {
	char *first;
	int min;
};

struct Memory {
	struct Variable {
		char name[20];
		char value[20];
	}variables[20];
	int variablesAdded;

	struct Label {
		char name[20];
		int line;
		int lastUsed;
	}labels[20];
	int labelsAdded;
};
