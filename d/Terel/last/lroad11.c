#pragma strict_types
#pragma binary_save

#include "/d/Terel/include/Terel.h"
inherit LAST_DIR+"last_room";

#include <stdproperties.h>

void
create_room()
{
    set_short("The town of Last");
    Extraline = "You're on the docks now to the east a pier drapes over "+
      "the water for a ship to dock. To the north two other "+
      "such piers can be seen. Walking west will bring you "+
      "to several shops down the road. A building is being erected to "+
      "south.";
    add_sea();
    add_road();
    add_mountain();
    add_snow();
    add_town();
    add_prop(ROOM_S_MAP_FILE, "town_last.txt");
	add_exit(LAST_DIR+"lroad10","north");
    add_exit(NPORT_DIR+"pier1","east",0);
    add_exit(LAST_DIR+"lroad8","west",0);
	add_exit(LAST_DIR+"gs_office/entrance", "south", 0);
    create_last_room();
}


