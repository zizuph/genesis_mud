#pragma strict_types

inherit "/d/Gondor/morgul/city/morgul.c";
#include "/d/Gondor/defs.h"

public void
create_morgul_room()
{
    set_extraline("From here you have a tremendous view over the " +
    "Morgul vale. Farther away you can see the green forests of " +
    "Ithilien and the blue band of the Anduin. You are here at " +
    "the northwestern corner of the city wall. It continues " +
    "south to the dark shadow of the great Tower and northeast " +
    "to the Morgul Gate.");
    set_road(1);
    set_side("northwest");

    add_tower();
    add_view_northwest();
    add_exit(MORGUL_DIR + "city/wall/wall20","northeast","@@check_exit",1);
    add_exit(MORGUL_DIR + "city/wall/wall18","south","@@check_exit",1);
}
