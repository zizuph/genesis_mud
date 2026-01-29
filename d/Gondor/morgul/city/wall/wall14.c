#pragma strict_types

inherit "/d/Gondor/morgul/city/morgul.c";
#include "/d/Gondor/defs.h"

public void
create_morgul_room()
{
    set_extraline("Here in the southwestern corner of the city the " +
    "great Tower touches the city walls. There is an entrance into " +
    "the tower. The city wall runs northwest around the great Tower, " +
    "while it continues to the east towards the Mordor Gate. " +
    "The steep cliffs of the mountains are rising high into the sky " +
    "only a few fathoms south of the city wall.");
  set_road(1);
  set_side("southwest");

    add_tower();
    add_view_south();
  add_exit(MORGUL_DIR + "city/wall/wall13", "east","@@check_exit",1);
  add_exit(MORGUL_DIR + "city/wall/wall15", "northwest","@@check_exit",1);

  clone_object(MORGUL_DIR + "tower/doors/southwall_out")->move(TO);
}
