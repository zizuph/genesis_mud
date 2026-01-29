int value(int amount)
{
  if (amount <= 0) return 0;
  write("Value of the food of amount "+amount+" will be ");
  write((amount*amount/600)+5);
  write("\n");
}

