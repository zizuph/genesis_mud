#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_wall("south");
    create_special(TOW_RUBBLE, "west");
    extra = "To the west, the way is blocked by what remains of a " +
        "small stone structure of some sort. It's completely beyond " +
        "identification, as what parts didn't fall in on their own " +
        "were crushed into sand by the weight of the tower. " +
        "To the immediate south, there's a large breach in " +
        "the wall where it's completely collapsed in upon " +
        "itself, producing an exit to the south into the " +
        "ruins. ";

    create_forest();
    
    add_item(({"structure", "remains", "stone structure"}),
        "Quite possibly, the shattered stone was once a small house " +
        "or stable of some sort, but that's a wild guess, as the " +
        "weight of the tower has oblitered everything but the general " +
        "shape of its foundation.\n");

    add_prop(DAGGER_AS_SEARCH_TARGETS, ({"structure", "remains",
        "stone structure"}));

    add_exit(FOREST + "n_forest_6", "north");
    add_exit(FOREST + "n_forest_10", "east");
    add_exit(RUIN + "in_north_arch", "south");
}
