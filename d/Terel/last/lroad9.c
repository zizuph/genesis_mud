#pragma strict_types
#pragma binary_save

#include "/d/Terel/include/Terel.h"
inherit LAST_DIR+"last_room";

#include <stdproperties.h>

void
create_room()
{
    set_short("The town of Last");
    Extraline = "You are at the edge of the docks, a dock juts out into the"+
                      " bay to the east. South you can see two more similar"+
                      " docks. You may travel west further into the town.";
    add_sea();
    add_road();
    add_mountain();
    add_snow();
    add_town();
    add_prop(ROOM_S_MAP_FILE, "town_last.txt");
	add_exit(NPORT_DIR+"pier4","east",0);
    add_exit(LAST_DIR+"lroad6","west",0);
    add_exit(LAST_DIR+"lroad10a","south",0);
    create_last_room();
}


