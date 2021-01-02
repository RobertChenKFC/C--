
  #include <stdio.h>

  void write(int x) {
    printf("%d", x);
  }

  void write(float x) {
    printf("%f", x);
  }

  void write(const char *x) {
    printf("%s", x);
  }

  int read() {
    //int x;
    //scanf("%d", &x);
    return 1381;
  }

  float fread() {
    //float x;
    //scanf("%f", &x);
    return -12.81;
  }

  int MAIN() {
  int a[100];
  int b[100];
  b[99] = 456;
  {
    int a[100];
    {
      int a[100];
      a[0] = 123;
      write(a[0]);
      write(b[99]);
    }
    a[0] = 456;
    write(a[0]);
    write(b[99]);
    {
      int b[100];
      b[99] = 666;
      write(a[0]);
      write(b[99]);
    }
  }
  /* this seems incorrect... */
  write(a[0]);
  write(b[99]);
}

  int main() {
    return MAIN();
  }
  