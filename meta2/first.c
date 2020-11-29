int funcao(int a, int b, int c, int d){
  int e = d*2;
  return a + b + c + e;
}

int main(void) {
  char i = 'A';
  while (i <= 'Z')
  {
    putchar(i);
    i = i + 1;
  }
  int a;
  int teste2;
  funcao(5, 6, 8, 2);
  return 0;
}
