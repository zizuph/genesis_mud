#include "defs.h"

inherit NTOWERBASE;

public void
create_room()
{
    extra = "The rubble is far too dense to the south " +
        "to make any progress, but it looks like you " +
        "can head northwards. What looks to have once " +
        "been a window provides a means of getting out " +
        "of the cramped quarters here.";

    add_item(({"window", "hole"}),
        "The window is now just a gaping hole in the east " +
        "wall here.\n");

    create_tower();

    add_exit(RUIN + "ntower2", "north");
    add_exit(RUIN + "nwalk4", "east");
}