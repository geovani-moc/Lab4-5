int f(int n) {
  int a;
  int b;
  a = n-1;
  b = f(a);
  return n * b ;
}
