#pragma strict_types
#pragma no_clone

inherit "/std/room";

#include <stdproperties.h>

public void
create_room()
{
  set_short("A hallway");
  set_long("You are in a hallway leading into the east wing of the " +
	   "Lord's manor. The hallway extends east and west.\n");
  
  add_exit("hallway02", "west");
  add_exit("hallway04", "east");
}
