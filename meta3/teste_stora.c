int A0, A1, A2, A3, A4;
short B1, B2, B3, B4;
char C0, C1, C2, C3, C4;
double D1, D2, D3, D4;
char argc; int argv; /* so para confundir */
void g0(void);
char g1(void);
int g2(void);
int f0( int, short, char, double);
char f1(int, short, char, double);
short f2(int, short, char, double);
double f3(int, short, char, double);
void f4(int, short, char, double);
int main(void) {
f0(A0, B1, C0, D1);
f1(A0, B1, C0, D1);
f2(A0, B1, C0, D1);
f3(A0, B1, C0, D1);
f4(A0, B1, C0, D1);
f1(f0(A0, B1, C0, D1), B1, C0, D1);
f2(f0(A0, B1, C0, D1), f1(f0(A0, B1, C0, D1), B1, C0, D1), C0, D1);
f3(f0(A0, B1, C0, D1), f1(f0(A0, B1, C0, D1), B1, C0, D1), f2(f0(A0, B1, C0, D1), f1(f0(A0, B1, C0, D1), B1, C0, D1), C0, D1), D1);
f4(f0(A0, B1, C0, D1), f1(f0(A0, B1, C0, D1), B1, C0, D1), f2(f0(A0, B1, C0, D1), f1(f0(A0, B1, C0, D1), B1, C0, D1), C0, D1), f3(f0(A0, B1, C0, D1), f1(f0(A0, B1, C0, D1), B1, C0, D1), f2(f0(A0, B1, C0, D1), f1(f0(A0, B1, C0, D1), B1, C0, D1), C0, D1), D1));
f4(B1, C1, C0, A1);
g0(), g1(), g2(), g0();
}