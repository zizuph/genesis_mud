inherit "/std/room";

#include "/d/Emerald/defs.h"

inherit SHIP_ROOM_BASE;

public void
create_room()
{
    set_short("Pier");
	set_long(break_string("You are standing on a long wooden dock.  Ships dock " +
	"here on occasion to carry travellers off to distant lands. " +
	"Seagulls soar over your head, and the water pounds beneath your feet. " +
	"A sign stands on a post near the edge of the pier.\n", 75));

    add_item("sign", "There is writing on it.\n");

	add_cmd_item("sign", "read", "The ship from Relic lands here.\n");
	add_exit(VOL + "pier2.c", "west");
	add_exit(VOL + "clear.c", "east");
/*
	set_ship_file("/d/Emerald/tmp/volcano/OBJS/ship.c");
    add_ship();
*/
}
