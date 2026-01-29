inherit "/d/Rhovanion/common/erebor/caves.c";

#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"
#define CAVE_DIR ERE_DIR + "ere1/"

create_cave()
{
  set_rock_type("cold grey granite");
  set_cave_name("the Lonely Mountain");
  set_region("northern");
  set_cave("Erebor");
  set_cave_type(7);
  set_long("Suddenly you realize that you have entered "
	 + "a room for the guards of Lonely Mountain. "
         + ""
         + ""
         + "In the centre of the room is a table with "
         + "four adjoining chairs. There seem to be some sort of beds "
         + "standing against the walls.");

  add_item(({"table"}),BS(
    "Its a ordinary table made out of wood, on the table where the chairs are " +
    "standing, the table looks very well worn. So obvviously there is always " +
    "guards in this room.!\n"));
  
  add_item(({"chair", "chairs"}),BS(
    "Seems like ordinary chairs just the size for dwarves.\n"));
  
  add_exit(CAVE_DIR + "lm1c2","west",0,1);
}
