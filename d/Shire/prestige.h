/*  Gives prestige to Knights who kill monsters including this
 *  file.  All npcs in the Shire should include this file, or have
 *  the code in it somewhere.
 */
query_knight_prestige()
{
  int i;
  if(this_object()->query_alignment() <= 0)
  {
    i = this_object()->query_average_stat();
    i = i * i / 10;
    return i;
  }
  else
  {
    i = this_object()->query_average_stat();
    i = -(i * 2 / 100);
    return i;
  }
}
