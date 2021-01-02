
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

  float r, pi;

float Calc() {
  float ret;
  ret = r * r * pi;
  return ret;
}

int MAIN() {
  pi = 3.14159;
  r = 1.0;
  write(Calc());
  write("\n");
  r = 0.0;
  write(Calc());
  write("\n");
  r = pi;
  write(Calc());
  write("\n");
  r = 100000000000.0000;
  write(Calc());
  write("\n");
  r = 1231232131.123;
  write(Calc());
  write("\n");
}

  int main() {
    return MAIN();
  }
  