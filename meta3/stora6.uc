void a;
int a;

void f1(void);
void f2(void){}
void f1(void){}
void f2(void);

void f2(void, void);
void f3(void, int);
void f4(char, void, int);

void f5(void x);
void f6(void, void y);
void f7(void, int x);
void f8(void x, int y);
void f9(char x, void);
void f10(char x, void y, int z);

void f11(void x){}
void f12(void, void y){}
void f13(void, int x){}
void f8(void x, int y){}
void f9(char x, void){}
void f10(char x, void y, int z){}

void f20(char x, char y, int z){void p; int p;}