#include "defs.h"

inherit GRAVEYARD_DIR + "under_church_hall";

void
create_hall()
{
    set_long("A narrow hallway runs between two chambers to the east and west.  " +
        "Along the length of the hallway, a series of archways on both sides have " +
        "been bricked up except for the passages directly to your north and south.\n");

    add_exit("train", "north");
    add_exit("library", "south");
    add_exit("under_church03", "east");
    add_exit("lair", "west");
}
