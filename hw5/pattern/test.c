int n;

int f(int a, int b, int c) {
  if (n <= 0)
    return a;
  n = 0;

  a = f(1, 1, 1);
  b = f(1, 1, 1);

  return c;
}

int MAIN() {
  n = 1;
  f(10, 10, 10);
  return 0;
}
