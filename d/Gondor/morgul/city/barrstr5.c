#pragma strict_types

inherit "/d/Gondor/morgul/city/morgul.c";
#include <macros.h>
#include "/d/Gondor/defs.h"

public void
create_morgul_room()
{
    set_extraline("The dark and narrow street ends here in the northeastern " +
    "corner of the city. To the north and the east, the city walls block " +
    "your progress, to the west a dark hole leads into an ancient " +
    "building that looks more like a ruin than a home. " +
    "A steep flight of stairs is leading up to the top of the walls here.");
    set_road(4);
    set_side("northeast");

    add_ruin();
    add_stairs();

    add_exit(MORGUL_DIR + "city/barrstr4","south","@@check_exit",1);
    add_exit(MORGUL_DIR + "city/barrack6","west","@@check_exit",1);
    add_exit(MORGUL_DIR + "city/wall/wall04","up",
        "@@stairs|up the narrow stairs leading up to the top of the walls@@",2);
}

