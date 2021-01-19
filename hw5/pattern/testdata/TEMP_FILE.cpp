
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
    int x;
    scanf("%d", &x);
    return x;
}

float fread() {
    float x;
    scanf("%f", &x);
    return x;
}
        int MAIN() {
    int a, b;
    float c, d;
    write("input:");
    a = read();
    write("input:");
    b = read();
    write("input:");
    c = fread();
    write("input:");
    d = fread();

    write(a);
    write("\n");
    write(b);
    write("\n");
    write(c);
    write("\n");
    write(d);
    write("\n");
    return 0;
}

int main() {
    return MAIN();
}
        