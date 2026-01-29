#pragma strict_types
#pragma binary_save

#include "/d/Terel/include/Terel.h"
inherit LAST_DIR+"last_room";

#include <stdproperties.h>

void
create_room()
{
    set_short("In front of a small building");
    Extraline = "The road continues to the east and west. The docks are visible"+
              " east, and the Sea of Terel unfolds to the horizon. A small building is "+
		"standing just north of the road.";
    add_sea();
    add_road();
    add_mountain();
    add_snow();
    add_town();
    add_prop(ROOM_S_MAP_FILE, "town_last.txt");
	add_exit(LAST_DIR+"lroad9","east",0);
    add_exit(LAST_DIR+"lroad3","west",0);
    add_exit(LAST_DIR + "bounty_office", "north", 0);
    create_last_room();
}

