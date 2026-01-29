inherit "/d/Rhovanion/common/erebor/caves.c";

#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"

create_cave()
{
  set_rock_type("cold grey granite");
  set_cave_name("the Lonely Mountain");
  set_region("northern");
  set_cave("Erebor");
  set_cave_type(5);
  set_long("This is the room where the guards retaining "
	 + "order in the Great Hall are stationed. With "
         + "all the Pubs and Taverns around they've got "
         + "a lot to do. "
         + "In the centre of the room is a table with "
         + "four adjoining chairs.");

  add_item("table","A sturdy birch table cramped with "
         + "dirty plates and empty goblets.\n");

  add_item(({"chair","chairs"}),"A rough-cut chair nailed "
         + "to floor.\n");

  add_exit(ERE_DIR + "lm1c11","south",0,1);
}
