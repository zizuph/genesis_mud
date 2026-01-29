#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
   extra = "To the south, the tower lies across what remains of a " +
        "small stone structure of some sort. It's completely beyond " +
        "identification, as what parts didn't fall in on their own " +
        "were crushed into sand by the weight of the tower. ";

    create_special(TOW_RUBBLE, "south");
    create_forest();
    
    add_item(({"structure", "remains", "stone structure"}),
        "Quite possibly, the shattered stone was once a small house " +
        "or stable of some sort, but that's a wild guess, as the " +
        "weight of the tower has oblitered everything but the general " +
        "shape of its foundation.\n");

    add_prop(DAGGER_AS_SEARCH_TARGETS, ({"structure", "remains",
        "stone structure"}));

    add_exit(FOREST + "n_forest_2", "north");
    add_exit(FOREST + "n_forest_6", "east");
    add_exit(FOREST + "n_forest_4", "west");
}
