
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
        

int a[4];
int visited[4];
int ans[4];

void dfs(int x){
  int i;
  if(x>=4){
    for(i=0;i<4;i=i+1){
      write(ans[i]);
    }
    write("\n");
    return;
  }
  for(i=0;i<4;i=i+1){
    if(visited[i]==0){
      visited[i]=1;
      ans[x]=a[i];
      dfs(x+1);
      visited[i]=0;
    }
  }
  return;
}

int MAIN(){
  int i;
  for(i=0;i<4;i=i+1){
    a[i]=i;
    visited[i]=0;
  }
  dfs(0);
  return 0;
}

int main() {
    return MAIN();
}
        