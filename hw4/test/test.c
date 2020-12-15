// a name cannot be declared more than once
typedef int INT; // ok
void f1() {}     // ok
INT x1;          // ok
void f1() {}     // redeclaration
int f1() {}      // redeclaration
INT x1;          // redeclaration
typedef int INT; // redeclaration

// A call to function must use the correct number of parameters
int f2(int a1, int a2, int a3) {
  f2(0,
     1);          // too few arguments
  f2(1,
     2,
     3,
     4);          // too many arguments
  float y = -7;   // ok
  while (1)
    return
      y;          // float to int
}

int f3(int a1[], int a2[100], int a3[][10], int a4[][20][10], int a5) {
  // Array references, except for actual parameters in function calls,
  // must match their declared dimensions
  int z = a1[0];
  while (z < 5) {
    a1 = a2[10][20][30];          // assign to array; subscript to non-array type
    a3[2] = a4[1][3];             // assign to array
    a1[0] = a4[1][2][3];          // ok
    a1[0] = a4[1]
              [3 + 2.2]
              [3];                // array subscript not integer
  }

  // An array name cannot be passed to a scalar formal parameter, and a scalar
  // cannot be passed to an array formal parameter
  int x ;
  for (x = 0; x < 10; x = x + 1)
    if (f2(4, 5, f2(7, 8, 9))) {
    } else if (x > f2(1,2,3)) {
      f3(1,
         2,
         3,
         4,
         5);                     // scalar to array

      f2(0,
         0,
         f3(a1,
            a2,
            a3,
            a4,
            a4));                // array to scalar
      f3(a4[2][3], a2, a4[2], a4, a3[0][1]); // ok
    }
  return z;
}

int main() {
  // every variable must be declared explicitly
  x = 5;    // undeclared
  y = g1(); // undeclared; undeclared
  T z;      // undeclared
  int l;    // ok
  while (8) {
    int u = 5; // ok
    u = u * 3; // ok
    u = l;     // ok
    z = l;     // undeclared
  }
  u = 7;    // undeclared

  // bonus
  INT a1[(40 * (-2)) + 300][-97 + 63 * 5 - 819];    // negative array size
  INT a2[(40 * (-2)) + 300][-97 + 63 * 5 - (-819)]; // ok
  INT a3[(40 * (-2.3)) + 300];                      // array size not int
  int a = 3, b = 7, c = a + b;                      // ok
  typedef 
    int
      INT;                                          // ok
  typedef
    float
      FLOAT;                              // ok
  typedef
    int
      FLOAT;                                // typedef redeclaration
  typedef INT INT;                                  // typedef redeclaration
  if (0) {
  } else {
    typedef float FLOAT;                            // ok
  }

  int a
    [1]
    [2];
  a
    [0] = 3;
}

int a = 3, b = 7, c = a + b; // initializer not constant
