/*
 * The road thru Frogmorton
 * By Finwe, September 1998
 */
 
#include "/d/Shire/sys/defs.h"
#include "defs.h"

#define GIFT_DIR   "/d/Shire/gift/"
 
inherit ROAD_BASE;
 
void
create_street()
{
    set_extraline("This is the west end of the village. The " +
        "road is well travelled as hobbits come and go this " +
        "way. A small wooden building sits to the west.\n");
    add_item(({"small building"}),
        "The building small and made of wood. Some activitiy " +
        "suggests that the building is popular in Frogmorton. " +
        "A sign fastened above the door swings in the breeze.\n");
 
    add_item("sign", 
        "The sign is made of wood and looks freshly painted. " +
        "Carved into its surface is an image of a hobbit with " +
        "a message.\n");
    add_cmd_item("sign", "read", "@@read_sign@@");
      
    add_exit(GIFT_DIR + "giftshop", "north");
    add_exit(FROG_DIR + "road04",  "east");
    add_exit(FROG_DIR + "po",      "west");
 
}
 
int
read_sign()
{
    write ("You read 'Frogmorton Messenger Service'.\n");
    say(QCTNAME(TP) + "reads the sign.\n");
    return 1;
}
