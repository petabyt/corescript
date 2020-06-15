#define COMMANDS 7
#define STRING_LENGTH 150

struct StringPart {
	int type;
	char string[STRING_LENGTH];
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
	}variables[50];
	int variablesAdded;

	struct Label {
		char name[20];
		int line;
		int lastUsed;
	}labels[50];
	int labelsAdded;
};
