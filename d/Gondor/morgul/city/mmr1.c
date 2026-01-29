#pragma strict_types

inherit "/d/Gondor/morgul/city/morgul.c";

#include <macros.h>

#include "/d/Gondor/defs.h"

public void
create_morgul_room()
{
    set_extraline("You are close to the great Morgul Gate. You can see a " +
        "flight of stairs leading up to the top of the walls on each side " +
        "of the road. To the south, you can see the dark shadow of the " +
        "Tower, while to the west a dark entrance leads into a building.");
    set_road(2);
    set_side("west");

    add_exit(MORGUL_DIR + "city/i_ngate","north","@@check_exit",1);
    add_exit(MORGUL_DIR + "city/wall/wall01","northeast",
       "@@stairs|up the narrow stairs leading up to the top of the walls@@",4);
    add_exit(MORGUL_DIR + "city/mmr2","south","@@check_exit",2);
    add_exit(MORGUL_DIR + "city/barrack1","west","@@check_exit",1);
    add_exit(MORGUL_DIR + "city/wall/wall20","northwest",
       "@@stairs|up the narrow stairs leading up to the top of the walls@@",4);

    add_barracks();
    add_item(({"gate","northern gate","morgul gate","dark gate"}), BS(
        "To the north, you can see the dark Morgul Gate. To both sides " +
        "of the road, narrow flights of stairs are leading up to the " +
        "top of the walls. \n"));
    add_item(({"stair","stairs","steps","flight"}),BS(
        "To both sides of the gate a narrow flight of stairs is leading " +
        "up to the top of the walls. From here, the feet of the stairs " +
        "are to the northwest and the northeast.\n"));
}

