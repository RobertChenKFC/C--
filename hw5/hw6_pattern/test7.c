int dim = 4;

int a[4][4];
/*
void print()
{
  int i,j;
  for (i = 0; i < dim; i = i + 1)
    {
      for (j = 0; j < dim; j = j + 1)
	{
	  write(a[i][j]);
          write(" ");
	}
      write("\n"); 
    }
}
*/
int MAIN()
{
  int i,j;
  /* DEBUG */
  int x;
  write("Enter matrix 1 of dim 4 x 4 : \n");

  for (i = 0; i < dim; i = i +1)
    {
      for (j = 0; j < dim; j = j +1)
	{
    /* DEBUG */
    write("BEFORE: i = ");
    write(i);
    write(", j = ");
    write(j);
    write("\n");

    /* DEBUG */
	  /*a[i][j] = read();*/
    x = read();

    /* DEBUG */
    write("THEN: i = ");
    write(i);
    write(", j = ");
    write(j);
    write("\n");

    /* DEBUG */
    a[i][j] = x;

    /* DEBUG */
    write("AFTER: i = ");
    write(i);
    write(", j = ");
    write(j);
    write("\n");
	}
    }
/*  print();*/
  write("done\n");
  return 0;
}


