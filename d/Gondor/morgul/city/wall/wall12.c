#pragma strict_types

inherit "/d/Gondor/morgul/city/morgul.c";
#include "/d/Gondor/defs.h"

public void
create_morgul_room()
{
    set_extraline("You are halfway between the great Tower and the " +
    "southeast tower of the city on the city wall. " +
    "The steep cliffs of the mountains are rising high into the sky " +
    "only a few fathoms south of the city wall.");
  set_road(1);
  set_side("south");

    add_tower();
    add_view_south();
  add_exit(MORGUL_DIR + "city/wall/wall11","east","@@check_exit",1);
  add_exit(MORGUL_DIR + "city/wall/wall13","west","@@check_exit",1);
}
