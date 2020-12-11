int funcao(int a, int b, int c, int d){
  int e = d*2;
  return a + b + c + e;
}

int funcao2(int n){
  return n%2;
}

int main(void) {
  char i = 'A';
  while (i <= 'Z')
  {
    putchar(i);
    i = i + 1;
  }
  int a = 2*(1+3);
  funcao(funcao2(10), 6, 8, 2);
  return 0;
}
