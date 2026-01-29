/*
 * /d/Terel/last/lroad2.c
 *
 * Created...long ago.
 *
 * Modified 11/29/2018 by Shanoga
 * - Added path to new bank.
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
    Extraline = "To the north is the White Dragon Inn. The road continues " +
        "to the east and west, while the Bank of Last is to the south.";
    add_road();
    add_mountain();
    add_snow();
    add_town();
    add_prop(ROOM_S_MAP_FILE, "town_last.txt");
	add_exit(LAST_DIR+"whdragon","north",0);
    add_exit(LAST_DIR+"lroad4","east",0);
    //add_exit(LAST_DIR+"lroad5","southeast","@@closed_construction@@");
    add_exit(LAST_DIR+"bank","south",0);
    add_exit(LAST_DIR+"lroad1","west",0);
    create_last_room();
}
/*
int
closed_construction()
{
    write("The southeast road is currently closed due to construction to " +
        "the south.\n");
    return 1;
}
*/