#pragma strict_types

inherit "/d/Gondor/morgul/city/morgul.c";
#include "/d/Gondor/defs.h"

public void
create_morgul_room()
{
    set_extraline("You are south of the great Mordor Gate. " +
    "Looking to the east, you can see how the city was built to " +
    "block the exits of Mordor. The city wall fills the space between " +
    "steep cliffs to the south and the deep vale of the Morgulduin to " +
    "the north. Looking down into the city to the west " +
    "you see the great tower of Minas Morgul dominating the view.");
  set_road(1);
  set_side("east");

    add_tower();
    add_view_east();
  add_exit(MORGUL_DIR + "city/wall/wall08","north","@@check_exit",1);
  add_exit(MORGUL_DIR + "city/wall/wall10","south","@@check_exit",1);
}
