int getVariable(char *name, struct Memory *memory);
int setVariable(char *name, char *value, struct Memory *memory);
void createVariable(char *name, char *value, struct Memory *memory);
int parseIntOrVar(int *error, char *string, int length, struct Memory *memory);
int executeFunction(char *result, char *string, struct Memory *memory);
int parseRaw(char *buffer, char *string, struct Memory *memory);
void parseString(char *buffer, struct Tree *tree, struct Memory *memory);
int findLabel(char *name, struct Memory *memory);
int gotoLabel(char *name, int l, struct Memory *memory);

int testCondition(int *error, char *operator, char *first, char *second, char l, struct Memory *memory);
