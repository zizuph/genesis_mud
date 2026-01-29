inherit "/d/Rhovanion/lib/caves.c";

#include "/d/Rhovanion/defs.h"
#include "door.h"
#include "def.h"
#include "/sys/macros.h"

  object door, key;

create_cave()
{
  set_rock_type("soluble limestone");
  set_cave_name("Thranduil's Caverns");
  set_region("northern");
  set_cave("Mirkwood");
  set_cave_type(1);
  set_long("You stand in a bend in the corridor, that is  leading " +
	   " east and south. To the north you see a door. " +
	   " \n");

  /* This is what is needed for the north door */
  door = clone_object(THIS_DIR + "C2_door");
  door -> move(TO);

  key = clone_object(THIS_DIR + "iron_key");
  key -> set_key(IRON);
  door -> set_key(IRON);

  set_noshow_obvious(1);
  add_exit(THIS_DIR + "cave45","east",0,1);
  add_exit(THIS_DIR + "cave41","south",0,1,);
}
