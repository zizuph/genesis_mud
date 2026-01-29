#pragma strict_types
#pragma binary_save

#include "/d/Terel/include/Terel.h"
inherit LAST_DIR+"last_room";

#include <stdproperties.h>

void
create_room()
{
    set_short("The road to Last");
    Extraline = "The road travels to both the east and the west.";
    add_road();
    add_mountain();
    add_snow();
    add_town();
    add_prop(ROOM_S_MAP_FILE, "town_last.txt");
	add_exit(LAST_DIR+"lroad2","east",0);
    add_exit("/d/Terel/n_port/np_road2","west",0);
    create_last_room();
}


