#pragma strict_types

inherit "/d/Gondor/morgul/city/morgul.c";
#include "/d/Gondor/defs.h"

public void
create_morgul_room()
{
    set_extraline("The dark and narrow street continues to the north " +
    "and the south. To the east is a money-changers joint, to the west " +
    "the hang-out for unemployed thugs and other adventurers.");
  set_road(3);
  set_side("south");

    add_tower();
    add_walls();
  add_exit(MORGUL_DIR + "city/darkstr2",        "north", "@@check_exit",1);
  add_exit(MORGUL_DIR + "city/rooms/bank",      "east",  "@@check_exit",1);
  add_exit(MORGUL_DIR + "city/darkstr0",        "south", "@@check_exit",1);
  add_exit(MORGUL_DIR + "city/rooms/boardroom", "west",  "@@check_exit",1);
}
