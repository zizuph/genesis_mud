#include "defs.h"

inherit MOUNTBASE;

public void
create_room()
{
    extra = "Off to the west, you note a framework of some sort " +
        "rising out of the rocky shore.";
    create_shore();

    add_exit(MOUNT + "mshore2", "west");
    add_exit(MOUNT + "m17", "south");
    add_prop(ROOM_I_TYPE, ROOM_BEACH);
    add_item(({"frame", "framework"}),
        "You can see a wooden frame of some sort planted in " +
        "the shore just west of here, but you can't make out any " +
        "more detail than that from here.\n");
}

public void
init()
{
    ::init();
    init_shore();
}
