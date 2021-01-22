int is_prime(int n) 
{
  int k, limit;


  if (n == 2) 
    return 1;

  /* DEBUG */
  /*
  write("testing if ");
  write(n);
  write(" is an even number (");
  write(n);
  write(" % 2 == ");
  write(n / 2 * 2);
  write(")\n");
  */

  if ((n/2 * 2)== n) 
    return 0; 
  limit = n / 2;
 
  for ( k = 3; k <= limit; k = k + 2) {
    /* DEBUG */
    /*
    write("testing if ");
    write(k);
    write(" is a factor of ");
    write(n);
    write("\n");
    */

    if ((n - (n/k * k)) == 0)
      return 0;
  }
  return 1;
}

int MAIN()
{
  int i, num1, num2;
  
  write("enter a range, for example, 5<ENTER> 23<ENTER>:");
  num1 = read();
  num2 = read();
 
  for (i =num1; i < num2; i = i + 1)
    {
      if (is_prime(i)) {
	write (i);
	write ("\n");
      }
    } 
  return 0; 
}


