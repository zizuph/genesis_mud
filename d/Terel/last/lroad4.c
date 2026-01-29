/*
 * /d/Terel/last/lroad4.c
 *
 * Created...long ago.
 *
 * Modified 11/29/2018 by Shanoga
 * - Added description of new bank.
 */
#pragma strict_types
#pragma binary_save

#include "/d/Terel/include/Terel.h"
inherit LAST_DIR+"last_room";

#include <stdproperties.h>

void
create_room()
{
    set_short("The town of Last");
    Extraline = "You've come to a crossroad in the town, you may go east " +
        "further into the town towards the docks, or north or south to " +
        "some of the establishments within the town. The building to the " +
        "southwest is the Bank of Last.";
    add_road();
    add_mountain();
    add_snow();
    add_town();
    add_prop(ROOM_S_MAP_FILE, "town_last.txt");
	add_exit(LAST_DIR+"lroad3","north",0);
    add_exit(LAST_DIR+"lroad5","south",0);
    add_exit(LAST_DIR+"lroad7","east",0);
    add_exit(LAST_DIR+"lroad2","west",0);
    create_last_room();
}