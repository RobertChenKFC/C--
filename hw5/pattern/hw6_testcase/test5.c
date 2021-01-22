
int a[10];
int b[10];
int c[10];

void merge(int Left,int Mid,int Right){
  int i,j,k, Len1, Len2;

  /* DEBUG */
  write("left: ");
  write(Left);
  write(", mid: ");
  write(Mid);
  write(", right: ");
  write(Right);
  write("\n");

  Len1=Mid-Left+1;
  Len2=Right-(Mid+1)+1;
  for(i=0;i<Len1;i=i+1){
    b[i]=a[Left+i];
  }
  for(i=0;i<Len2;i=i+1){
    c[i]=a[(Mid+1)+i];
  }
  i=0;
  j=0;
  k=Left;
  while((i<Len1)&&(j<Len2)){
    if(b[i]<=c[j]){
      a[k]=b[i];
      i=i+1;
    }
    else{
      a[k]=c[j];
      j=j+1;
    }
    k=k+1;
  }
  while(i<Len1){
    a[k]=b[i];
    i=i+1;
    k=k+1;
  }
  while(j<Len2){
    a[k]=c[j];
    j=j+1;
    k=k+1;
  }
  return;
}

void mergesort(int Left,int Right){
  int Mid;
  /* DEBUG */
  int test1, test2, test3, test4;

  /* DEBUG */
  write("left: ");
  write(Left);
  write(", right: ");
  write(Right);
  write("\n");

  Mid=(Left+Right)/2;
  if(Left>=Right){
    return;
  }

  /* DEBUG */
  /*
  write("calling left = ");
  write(Left);
  write(", mid = ");
  write(Mid);
  write("\n");
  */
  test1 = Mid;
  test2 = Mid;
  test3 = Mid;
  test4 = Mid;

  /* DEBUG */
  if (Mid != test1 || Mid != test2 || Mid != test3 || Mid != test4) {
    write("FAIL1! Mid = ");
    write(Mid);
    write(", test1 = ");
    write(test1);
    write(", test2 = ");
    write(test2);
    write(", test3 = ");
    write(test3);
    write(", test4 = ");
    write(test4);
    write("\n");
    return;
  }

  mergesort(Left,Mid);

  /* DEBUG */
  if (Mid != test1 || Mid != test2 || Mid != test3 || Mid != test4) {
    write("FAIL2! Mid = ");
    write(Mid);
    write(", test1 = ");
    write(test1);
    write(", test2 = ");
    write(test2);
    write(", test3 = ");
    write(test3);
    write(", test4 = ");
    write(test4);
    write("\n");
    return;
  }

  /* DEBUG */
  /*
  if (Mid + 1 == 65) {
    write("SPECIAL: ");
  }
  write("calling mid+1 = ");
  write(Mid+1);
  write(", right = ");
  write(Right);
  write("\n");
  */

  mergesort(Mid+1,Right);
  merge(Left,Mid,Right);
}

int MAIN(){
  int i;
  a[0]=2;
  a[1]=10;
  a[2]=3;
  a[3]=8;
  a[4]=1;
  a[5]=9;
  a[6]=4;
  a[7]=7;
  a[8]=6;
  a[9]=5;
  
  mergesort(0,9);
  
  
  for(i=0;i<10;i=i+1){
    write(a[i]);
    write("\n");
  }
  return 0;
}
