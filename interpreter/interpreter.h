int findVariable(struct Memory memory, char *name);
void setVariable(struct Memory *memory, char *name, char *string);
int tryInt(int *result, char *string);
int tryIntOrVariable(struct Memory memory, int *result, char *string);
int findLabel(struct Memory memory, char *string);
int gotoLabel(struct Memory memory, char *label, int l);
int gotoLabelLastUsed(struct Memory memory, char *label, int l);

int doCalculation(struct Memory memory, int *result, char parts[20][20]);
void afterColon(char *whole, char *after);
