/*
 * The road thru Frogmorton
 * By Finwe, September 1998
 */
 
#include "/d/Shire/sys/defs.h"
#include "defs.h"
 
inherit ROAD_BASE;

void
create_street()
{
    set_extraline("This is the center of Frogmorton. Burrows " +
        "and smials line the road here as " +
        "well as some houses. A stone building is to the " +
        "west. It's rather odd and stands out from the rest of " +
        "the buildings here.\n");
    add_item(({"large building"}),
        "The building is is made of stone It looks like it's " +
        "able to withstand anything. Nonetheless an " +
        "occasional laughing can be heard from within. A sign " +
        "has been fastened above the door.\n");
 
    add_item("sign", 
        "The sign is made of wood and looks freshly painted. " +
        "Carved into its surface is an image of a hat with a " +
        "feather in it.\n");
    add_cmd_item("sign", "read", "@@read_sign@@");
 
 
     
    add_exit(FROG_DIR + "road04",   "north");
    add_exit(FROG_DIR + "road01",   "south");
    add_exit(FROG_DIR + "smial02", "east");
    add_exit(FROG_DIR + "police",   "west");
 
}
 
int
read_sign()
{
    write ("You read 'Headquarters of the East Farthing Troop " +
        "of the Watch'.\n");
    say(QCTNAME(TP) + "reads the sign.\n");
    return 1;
}
