#pragma strict_types
#pragma no_clone

inherit "/std/room";

#include <stdproperties.h>

public void
create_room()
{
  object door;
  set_short("A hallway");
  set_long("You are in a hallway leading into the east wing of the " +
	   "Lord's manor. The hallway extends east and west.\n");
  
  add_exit("hallway01", "west");
  add_exit("hallway03", "east");
  door = clone_object("/d/Earthsea/gont/gont_city/obj/doors/study_door_out");
  door->move(this_object());
}
