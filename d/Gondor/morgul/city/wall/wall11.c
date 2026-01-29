#pragma strict_types

inherit "/d/Gondor/morgul/city/morgul.c";
#include "/d/Gondor/defs.h"

public void
create_morgul_room()
{
    set_extraline("You are on the city wall close to the southeast tower " +
    "of the city east of you. The wall continues westwards to the great " +
    "Tower. The steep cliffs of the mountains are rising high into the " +
    "sky only a few fathoms south of the city wall.");
  set_road(1);
  set_side("south");

    add_tower();
    add_view_south();
  add_exit(MORGUL_DIR + "city/wall/wall10","east","@@check_exit",1);
  add_exit(MORGUL_DIR + "city/wall/wall12","west","@@check_exit",1);
}
