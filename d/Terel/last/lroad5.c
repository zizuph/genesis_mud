/*
 * /d/Terel/last/lroad5.c
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
    Extraline = "To the south is the Armour shop, towards the east you can " +
        "see another similar shop. North will take you to a crossroads in " +
        "town, while the Bank of Last is to the west.";
    add_road();
    add_mountain();
    add_snow();
    add_town();
    add_prop(ROOM_S_MAP_FILE, "town_last.txt");
	add_exit(LAST_DIR+"lroad4","north",0);
    add_exit(LAST_DIR+"armshop","south",0);
    add_exit(LAST_DIR+"lroad8","east",0);
    //add_exit(LAST_DIR+"lroad2","northwest","@@closed_construction@@");
    add_exit(LAST_DIR+"bank","west",0);
    create_last_room();
}
/*
int
closed_construction()
{
    write("The northwest road is currently closed due to construction " +
        "to the west.\n");
    return 1;
}
*/