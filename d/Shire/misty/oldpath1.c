#include <stdproperties.h>
#include <macros.h>
#include "local.h"

inherit SHIRE_ROOM;

void
create_shire_room()
{
    set_short("Old path");
    set_long("This grassy path is surprisingly pleasant considering " +
        "how close to Mirkwood it is.  Back to the west are the " +
        "Misty Mountains, and to the east lurks Mirkwood forest.  " +
        "You can wander in the vale of Anduin to the north and the " +
        "south.  Looking north, you vaguely make out a tall spire of " +
        "rock.\n");

    add_exit(MISTY_DIR + "p13", "west");
    add_exit(MISTY_DIR + "oldpath2", "east");
}
