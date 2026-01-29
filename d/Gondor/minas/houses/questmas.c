/* The object that keeps track of variables in Elessar's quests. */

/*  Herb-smuggler quest functions and variables */
int runaway;
object carrier,herb;

set_carrier(object obj)
{
  carrier = obj;
}

query_carrier()
{
  return carrier;
}

set_herb(object obj)
{
  herb = obj;
}

query_herb()
{
  return herb;
}

set_runaway(int i)
{
  runaway = i;
}

query_runaway()
{
  return runaway;
}

reset_herb_quest()
{
  runaway = 0;
  carrier = 0;
  herb = 0;
}

/* Reveal Spy Quest - functions and variables. */
object dog_drugger;
