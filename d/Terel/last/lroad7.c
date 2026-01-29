#pragma strict_types
#pragma binary_save

#include "/d/Terel/include/Terel.h"
inherit LAST_DIR+"last_room";

#include <stdproperties.h>

void
create_room()
{
    set_short("The town of Last");
    Extraline = "The road here allows you to travel either east to "+
                      "the docks or west towards the west entrance of "+
                      "town. To the north is a pub of sorts and to the "+
                      "south you can hear the hammering of the local "+
                      "smith.";
    add_road();
    add_mountain();
    add_snow();
    add_town();
    add_prop(ROOM_S_MAP_FILE, "town_last.txt");
	add_exit(LAST_DIR+"snowhouse","north",0);
    add_exit(LAST_DIR+"smithy","south",0);
    add_exit(LAST_DIR+"lroad10","east",0);
    add_exit(LAST_DIR+"lroad4","west",0);
    create_last_room();
}
