#pragma strict_types
#pragma binary_save

#include "/d/Terel/include/Terel.h"
inherit LAST_DIR+"last_room";

#include <stdproperties.h>

void
create_room()
{
    set_short("The town of Last");
    Extraline = "The road leads east to the docks or west towards "+
                      "the entrance to the town. South is the weapon "+
                      "shop of the town.";
    add_sea();
    add_road();
    add_mountain();
    add_snow();
    add_town();
    add_prop(ROOM_S_MAP_FILE, "town_last.txt");
	add_exit(LAST_DIR+"wepshop","south",0);
    add_exit(LAST_DIR+"lroad11","east",0);
    add_exit(LAST_DIR+"lroad5","west",0);
    create_last_room();
}

