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
    set_extraline("This is the crossroads of Frogmorton. The " +
        "road goes east and west here to other areas of the " +
        "village. A large building stands north of here and " +
        "seems to see quite a bit of activity.\n");
    add_item(({"large building"}),
        "The building is is made of wood. It looks like it's " +
        "able to withstand anything. Hobbits come and go from " +
        "it. A sign fastened above the door swings in the " +
        "breeze.\n");
 
    add_item("sign", 
        "The sign is made of wood and looks freshly painted. " +
        "Carved into its surface is an image of some goods.\n");
    add_cmd_item("sign", "read", "@@read_sign@@");
 
 
     
    add_exit(FROG_DIR + "shop",   "north");
    add_exit(FROG_DIR + "road02", "south");
    add_exit(FROG_DIR + "road05", "east");
    add_exit(FROG_DIR + "road03", "west");
 
}
 
int
read_sign()
{
    write ("You read 'Frogmorton Sundries'.\n");
    say(QCTNAME(TP) + "reads the sign.\n");
    return 1;
}
