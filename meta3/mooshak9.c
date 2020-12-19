/* Semantic errors in declarations involving parameter names */

/* Declarations */
void f1(void);
char f2(int a);
int f3(char a);

void f4(int a, short b, double c);
int f5(char a, int b, int c);
double f6(short a, double b, int c);
double f7(short a, double b, int b);

/* Redeclarations - different parameter names */

void f1(void);
char f2(int A);
int f3(char A);

void f4(int A, short B, double C);
int f5(char d, int e, int f);
double f6(short d, double e, int f);


/* Redeclarations - different return type */

char f1(void);
int f2(int a);
void f3(char a);

int f4(int A, short B, double C);
double f5(char d, int e, int f);
void f6(short d, double e, int f);

/* Redeclarations - more arguments */

int f2(int a, int b);
void f3(char a, char b);
int f2(int a, int);
void f3(char a, char);

void f4(int a, short b, double c, char f);
int f5(char a, int b, int c, double e);
double f6(short a, double b, int c, char u);

void f4(int a, short b, double c, char f, double t);
int f5(char a, int b, int c, double e, char t);
double f6(short a, double b, int c, char u, short i);

/* Redeclarations - fewer arguments */

char f2(void);
int f3(void);

void f4(int a, short b);
int f5(char a, int b);
double f6(short a, double b);

void f4(int a);
int f5(char a);
double f6(short a);

/* Redeclarations - different arguments */

void f1(int a);
char f2(char);
int f3(void);

void f4(int a, double b, double c);
int f5(char a, int b, double c);