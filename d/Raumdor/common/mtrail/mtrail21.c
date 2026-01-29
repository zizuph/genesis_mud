/* Mountain trail room, credit to Sarr */
#pragma strict_types
#include "defs.h"
inherit MTRAIL_ROOM;

void
create_room()
{
    ::create_room();
    set_long("You are in an inaccessible area. Hopefully you're a wizard!\n");
    add_item("castle","You can barely see it from this distance, but "+
    "it does look like some sort of castle or fortress.\n");
    add_exit(MTRAIL_DIR + "mtrail07", "south", "@@block", 2);
}

int
block()
{
    write("The trail blocked by a tretcherous-looking rock slide. " +
        "It seems impassable at this moment.\n");
    say(QCTNAME(TP)+" tries to go north but fails.\n");
    return 1;
}
