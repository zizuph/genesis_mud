#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    extra = "To the north, the crumbling remains " +
        "of a smaller structure stand. Whatever its purpose was while it " +
        "stood, it serves now only as an obstacle, and a place for moss " +
        "and small plants to find root. ";

    create_forest();

    add_item(({"remains", "structure", "smaller structure"}),
        "These ruins may have once been someone's home, but now are " +
        "home only to a myriad of insects and plant life.\n");

    add_prop(DAGGER_AS_SEARCH_TARGETS, ({"structure", "ruins", 
        "rubble"}));

    add_exit(FOREST + "w_forest_7", "east");
    add_exit(FOREST + "w_forest_9", "south");
    add_exit(FOREST + "w_forest_5", "west");
}
