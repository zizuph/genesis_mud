#pragma strict_types

inherit "/d/Gondor/morgul/city/morgul.c";
#include "/d/Gondor/defs.h"

public void
create_morgul_room()
{
    set_extraline("The northeast tower of the city is mounted in front " +
    "of the city walls where the northern and eastern walls meet. " +
    "To the north, you can look down into the vale of the Morgulduin, " +
    "to the east you see the dark slopes of the Ephel Duath rising " +
    "towards the pass high above the city. A flight of stairs is " +
    "leading down to the city streets here and through a doorway " +
    "to the northeast, one can enter the tower.");
  set_road(1);
  set_side("northeast");

  add_item(({"tower","northeast tower","doorway"}), BSN(
    "The northeast tower is only a few meters higher than the walls themselves. " +
    "It is mounted in front of the walls so that from the tower one " +
    "has a clear view of the outer side of the city walls. From here, one " +
    "can enter the tower through a doorway to the northeast."));
    add_view_east();
    add_view_north();
    add_stairs_down();
  add_exit(MORGUL_DIR + "city/wall/wall03","west","@@check_exit",1);
  add_exit(MORGUL_DIR + "city/towers/ne_tow2","northeast","@@block_npc",1);
  add_exit(MORGUL_DIR + "city/wall/wall05","south","@@check_exit",1);
  add_exit(MORGUL_DIR + "city/barrstr5","down","@@block_npc",1);
}

