inherit "/std/room";

#include "/d/Emerald/defs.h"

void create_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    set_short("Winding stairs in tower");
    set_long("    You are climbing the winding stairs of the "+
	     "tower.  They continue up and down from here.\n\n");

    add_exit(VILLAGE_DIR + "top", "up", 0);
    add_exit(VILLAGE_DIR + "stairs1", "down", 0);
}
