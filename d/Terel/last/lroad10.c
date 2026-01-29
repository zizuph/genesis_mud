#pragma strict_types
#pragma binary_save

#include "/d/Terel/include/Terel.h"
inherit LAST_DIR+"last_room";

#include <stdproperties.h>

void
create_room()
{
    set_short("The town of Last");
    Extraline = "On the edge of the docks, to the east a pier stretches"+
      " out onto the water for a ship to dock. To the north "+
      "and south two other piers are visible. West leads "+
      "into the heart of the town.";
    add_sea();
    add_road();
    add_mountain();
    add_snow();
    add_town();
    add_prop(ROOM_S_MAP_FILE, "town_last.txt");
	add_exit(LAST_DIR+"lroad10a","north");
    add_exit(LAST_DIR+"lroad11","south",0);
    add_exit(LAST_DIR+"lroad7","west",0);
    add_exit(NPORT_DIR+"pier2","east",0);
    create_last_room();
}

