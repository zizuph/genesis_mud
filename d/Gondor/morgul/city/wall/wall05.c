#pragma strict_types

inherit "/d/Gondor/morgul/city/morgul.c";
#include "/d/Gondor/defs.h"

public void
create_morgul_room()
{
    set_extraline("The northeast tower of the city is not far north from " +
    "here. To the south, you can see the great Mordor Gate. " +
    "To the east, you can see how the city was built to " +
    "block the exits of Mordor. The city wall fills the space between " +
    "steep cliffs to the south and the deep vale of the Morgulduin to " +
    "the north. Looking down over the city to the west " +
    "you see the great tower of Minas Morgul dominating the view.");
    set_road(1);
    set_side("east");

    add_tower();
    add_view_east();
    add_stairs_down();
    add_exit(MORGUL_DIR + "city/wall/wall04","north","@@check_exit",1);
    add_exit(MORGUL_DIR + "city/wall/wall06","south","@@check_exit",1);
}
