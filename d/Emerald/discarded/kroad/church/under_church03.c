#include "defs.h"

inherit GRAVEYARD_DIR + "under_church_hall";

void
create_hall()
{
    set_long("   A narrow hallway runs between two chambers to the east and " +
        "west.  A smaller passage leads a short way to the north.\n");

    add_exit("under_church05", "north");
    add_exit("under_church02", "east");
    add_exit("under_church04", "west");
    add_exit("storage", "south");
}
