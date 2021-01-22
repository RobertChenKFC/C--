int n;

int f(int a, int b, int c) {
  int x, y, z, m;

  if (n <= 0)
    return a;
  m = n;

  n = m - 1;
  x = f(x, y, z);

  n = m - 1;
  y = f(x, y, z);

  n = m - 1;
  z = f(x, y, z);

  return z;
}

int MAIN() {
  int x, y;

  n = 1;

  x = 10;
  y = x;
  if (x != y)
    write("FAIL1\n");

  f(x, x, x);
  if (x != y)
    write("FAIL2\n");

  write("complete!!!\n");
  return 0;
}
