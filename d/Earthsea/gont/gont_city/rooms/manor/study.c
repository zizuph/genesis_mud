#pragma strict_types
#pragma no_clone

inherit "/std/room";

#include <stdproperties.h>

public void
create_room()
{
  object door;
  set_short("The study");
  set_long("An oak desk dominates the room and from looks of the " +
	   "large heap of the paper on top of the desk, it is " +
	   "evident that the study's occupier is not too well " +
	   "organized. There is a bed at the other end of the room, " +
	   "whoever works here also sleeps here. There is a window " +
	   "at the north end of the room to allow natural light to " +
	   "permeate through.\n");

  add_item("bed", "It is a very austere straw filled cot.\n");
  add_item("window", "Sun light permeates the room through the window.\n");
  door = clone_object("/d/Earthsea/gont/gont_city/obj/doors/study_door_in");
  door->move(this_object());
}
