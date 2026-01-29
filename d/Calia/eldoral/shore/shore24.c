#include "defs.h"

inherit SHOREBASE;

public void
create_room()
{
    create_shore();
    main += "The structure of the shoreline changes abruptly to the " +
        "northwest, " +
        "as the pebbly surface rises sharply into sheer stone to meet a " +
        "low cliff that seems to mark the western edge of the island with " +
        "a sheer drop straight down to the water. The height of the " +
        "cliff isn't excessive, but the jaggedness of the cliff " +
        "face itself makes thoughts of climbing pointless. ";
    add_item(({"cliff", "cliff face"}),
        "Rising out of the shore to the northwest, the cliff " +
        "is low, but jagged, and completely impossible to " +
        "attempt climbing.\n");
    create_direction("west");

    add_exit(FOREST + "w_forest_8", "north", "@@woods_msg");
    add_exit(FOREST + "w_forest_11", "east", "@@woods_msg");
    add_exit(SHORE + "shore25", "south");
}
