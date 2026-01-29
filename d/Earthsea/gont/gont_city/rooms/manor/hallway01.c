#pragma strict_types
#pragma no_clone

inherit "/std/room";

#include <stdproperties.h>

public void
create_room()
{
  set_short("A hallway");
  set_long("You are in a hallway leading into the east wing of the " +
	   "Lord's manor. The entrance of the manor is to the west " +
	   "and the rest of the wing is to the east.\n");
  add_exit("manor_entrance", "west");
  add_exit("hallway02", "east");
}
