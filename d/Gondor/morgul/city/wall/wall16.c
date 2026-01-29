#pragma strict_types

inherit "/d/Gondor/morgul/city/morgul.c";
#include "/d/Gondor/defs.h"

public void
create_morgul_room()
{
    set_extraline("From here you have a tremendous view over the " +
    "western end of the Morgul vale. Farther away you can see " +
    "the green forests of " +
    "Ithilien and the blue band of the Anduin. You are here " +
    "close to the great Tower on the city wall. The wall continues " +
    "south to the dark shadow of the great Tower and north " +
    "to the Morgul Gate.");
  set_road(1);
  set_side("west");

    add_tower();
    add_view_northwest();
    add_exit(MORGUL_DIR + "city/wall/wall17","north","@@check_exit",1);
    add_exit(MORGUL_DIR + "city/wall/wall15","south","@@check_exit",1);
}
