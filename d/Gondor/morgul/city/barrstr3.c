#pragma strict_types

inherit "/d/Gondor/morgul/city/morgul.c";
#include <macros.h>
#include "/d/Gondor/defs.h"

public void
create_morgul_room()
{
    set_extraline("You are just north of the great Mordor Gate in a narrow " +
    "and dark street at the foot of the eastern city wall. A steep " +
    "flight of stairs is leading up to the top of the walls here. " +
    "To the west, you can see the dark entrance into an old building.");

    set_road(4);
    set_side("east");

    add_barracks();
    add_stairs();

    add_exit(MORGUL_DIR + "city/barrstr4","north","@@check_exit",1);
    add_exit(MORGUL_DIR + "city/mmr5","south","@@check_exit",1);
    add_exit(MORGUL_DIR + "city/barrack8","west","@@check_exit",1);
    add_exit(MORGUL_DIR + "city/wall/wall07","up",
        "@@stairs|the narrow stairs leading up to the top of the walls@@", 2);
}

