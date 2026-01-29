#pragma strict_types

inherit "/d/Gondor/morgul/city/morgul.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_morgul_room()
{
  object door;
    set_extraline("This is the basement of a large building. All around " +
    "you are walls made from dark roughly hewn boulders. There is a ladder " +
    "leaning on one wall. A tunnel is steeply sloping downwards in the " +
    "northeast corner of the room.");
  add_item(({"tunnel","corner"}), BSN(
    "In the northeast corner of the room, a dark tunnel is leading downwards. "));
  add_item(({"floor","ground"}), BSN(
    "The floor seems to be made out of the living rock of the Ephel Duath. " +
    "It as dark as the boulder of the walls. "));
  add_item(({"ceiling","roof","hole","opening"}), BSN(
    "The ceiling seems to be made of the same dark boulders as the walls. Above " +
    "the ladder there is a hole in the ceiling. "));
  add_item(({"ladder"}), BSN(
    "A rickety ladder is leaning on one wall. Above it in the ceiling you see " +
    "an opening. "));
  add_item(({"wall","walls","stones"}), BSN(
    "The walls of the basement are made from roughly hewn black boulders. The " +
    "walls look like they are the foundation of a mighty building rising over " +
    "your head. They are so black that is seems as if they are swallowing any " +
    "light that might come down here. Leaning on one wall is a ladder. "));
  set_road(5);
  set_side("northeast");

  add_exit(MORGUL_DIR + "tunnel/mmtun9","down","@@check_exit",3);
  add_prop(ROOM_I_LIGHT,-1);
  door = clone_object(MORGUL_DIR + "city/doors/bne1trapdown");
  door->move(TO);
}

