int f(int n) {
  int a;
  int b;
  b = 1;
  if ((n < 1) == 0) {
    a = n-1;
    b = f(a);
  }
  return n * b ;
}
