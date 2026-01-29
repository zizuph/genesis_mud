inherit "/std/room";

#include "/d/Emerald/defs.h"

void create_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    set_short("Winding stairs in tower");
    set_long("   You are climbing the winding stairs of the "+
	     "tower. They continue up and down from here. There is a plaque "+
	     "on the wall here.\n\n");

    add_item("plaque", "There is some writing on it.\n");

    add_exit(VILLAGE_DIR + "stairs2", "up", 0);
    add_exit(VILLAGE_DIR + "ground", "down", 0);
}

void
init()
{
    ::init();
    add_action("read", "read");
}

int
read(string arg)
{
    notify_fail("Read what?\n");
    if (arg != "plaque")
	return 0;
    write("It reads `Raised in honor of the great magician Plugh'.\n");
    return 1;
}
