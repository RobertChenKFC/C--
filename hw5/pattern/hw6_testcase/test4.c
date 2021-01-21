
int a[10];

void quicksort(int Left,int Right){
  int pivot, i, j, tmp;

  /* DEBUG */
  write("left: ");
  write(Left);
  write(", Right: ");
  write(Right);
  write("\n");

  pivot = Left;
  i = Left;
  j = Right;
  if(Left>=Right){
    return;
  }
  
  /* DEBUG */
  write("left: ");
  write(Left);
  write(", Right: ");
  write(Right);
  write("\n");

  /* DEBUG */
  /*
  write("pivot = ");
  write(a[pivot]);
  write("\n");
  */

  while(i<j){
    /* DEBUG */
    /*
    write("i:");
    */

    /*
    while((a[i]<=a[pivot])&&i<Right){
      i=i+1;
      */

      /* DEBUG */
      /*
      write(" ");
      write(i);
      write(" (");
      write(a[i]);
      write(")");
      */
    /*
    }
    */

    /* DEBUG */
    write(", j:");
    write(j);
    write("\n");
    j = -1;

    while(j>=Left){
      j=j-1;

      /* DEBUG */
      write(" ");
      write(j);
      /*
      write(" (");
      write(a[j]);
      write(")");
      */
    }

    /* DEBUG */
    /*
    write("\n");
    */

    /*
    if(i<j){
      tmp=a[i];
      a[i]=a[j];
      a[j]=tmp;
    }
    */
  }
  /*
  tmp=a[pivot];
  a[pivot]=a[j];
  a[j]=tmp;
  quicksort(Left,j-1);
  quicksort(j+1,Right);
  */

  /* DEBUG */
  /*
  for(i=0;i<10;i=i+1){
    write(a[i]);
    write(" ");
  }
  write("\n");
  */
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
  quicksort(0,9);
  
  for(i=0;i<10;i=i+1){
    write(a[i]);
    write("\n");
  }
  return 0;
}
