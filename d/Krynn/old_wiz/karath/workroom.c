inherit "/std/workroom";

void
create_workroom()
{
  set_long("     Smoke invades your lungs and the smell of "+
  "brimstone fills your nose. Four giant granite pillars rise "+
  "on all four sides of you and a dark throne rises out of the "+
  "mists before you. A stone stairwell decends through a rift in "+
  "the floor.\n");
  set_short("Karath's lair");
  add_exit("/d/Emerald/workroom", "emerald");
  add_exit("/d/Krynn/workroom", "krynn");
  add_exit("clone.c", "down");
     add_exit("is_working_rl.c", "work");
}
