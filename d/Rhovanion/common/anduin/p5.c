inherit "/d/Rhovanion/lib/room";

#include "/d/Rhovanion/defs.h"

create_room()
{
    set_short("Edge of Mirkwood");
    set_long("Massive black-leaved trees loom over the path here as you " +
        "stand at the break between Anduin and Mirkwood Forest.  Shadows " +
        "cling to your hands and shroud the area in darkness.\n");

    add_exit(ANDUIN_DIR + "p4", "south");
    add_exit(MIRK_DIR+"mirk-2-10-P", "east");
}

