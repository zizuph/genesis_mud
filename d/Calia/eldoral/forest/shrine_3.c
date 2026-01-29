#include "defs.h"

inherit SHRINEBASE;

public void
create_room()
{
    set_long("You are inside a small building of some sort. " +
        "All clues as to what it might once have been are gone, " +
        "as all the walls are bare, and the floor is now host " +
        "to nothing but a deep layer of dried out needles that " +
        "have blown through the archway leading out to the " +
        "north. The building's construction is quite plain, too, " +
        "looking like someone merely attached a number of large " +
        "vertical slabs for walls to one horizontal one for a " +
        "ceiling. The stone is a bit strange, however, it appears " +
        "to be much darker than the rest of the stone on the " +
        "isle, which is mostly some sort of grey granite.\n\n");

    create_shrine();

    add_exit(FOREST + "e_forest_24", "north");
}
