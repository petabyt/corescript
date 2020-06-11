int findVariable(struct Memory memory, char *name);
void setVariable(struct Memory *memory, char *name, char *string);
int tryInt(int *result, char *string);
int tryIntOrVariable(struct Memory memory, int *result, char *string);
int findLabel(struct Memory memory, char *string);
int gotoLabel(struct Memory memory, char *label, int l, int type);

int doCalculation(struct Memory memory, int *result, char p1[], char p2[], char p3[]);
void afterColon(char *whole, char *after);
