int f0( int, short, char, double);

int f0( int a , short b, char c, double d, int e){
    a=1;
}

int main(void){
    int a=1;
    short b = 2;
    char c = 'a';
    double d = 2.0;
    f0(a,b,c,d);
}