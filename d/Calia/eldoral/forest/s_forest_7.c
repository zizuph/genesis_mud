#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    extra = "You notice a massive grey boulder rising from beneath " +
        "the covering of ferns, like a lone, barren island upon " +
        "a strange sea of green. ";
    add_item(({"boulder", "massive boulder", "grey boulder",
        "massive grey boulder"}),
        "The boulder is enormous, and even though what shows " +
        "stands as high as you, it looks like almost half of " +
        "it could be buried.\n");
    create_wall("north");
    create_forest();
    add_exit(FOREST + "e_forest_2", "east");
    add_exit(FOREST + "s_forest_17", "south");
    add_exit(FOREST + "s_forest_6", "west");
}
