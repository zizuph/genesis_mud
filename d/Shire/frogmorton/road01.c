/*
 * The road thru Frogmorton
 * By Finwe, September 1998
 */
 
#include "/d/Shire/sys/defs.h"
#include "defs.h"

inherit ROAD_BASE;

#define WEST_R_DIR "/d/Shire/eastroad/western/" 
 
void
create_street()
{
    set_extraline("The road wanders north past some " +
        "smials and a few buildings. A large building is to " +
        "the east of here. Lively sounds come from it and a " +
        "sign sways in the breeze above the door. South is the " +
        "Great East Road.");

    add_item(({"large building", "floating log"}),
        "This building is one of the few wooden buildings in " +
        "the village. Some windows run across the fron of the " +
        "building with a door set in the middle of the " +
        "building. A sign swings above the door.\n");
    add_item("sign", 
        "The sign is faded but you can make out a log bobbing " +
        "in a stream carved into it.\n");

    add_cmd_item("sign", "read", "@@read_sign@@");
 
 
     
    add_exit(FROG_DIR + "road02",   "north");
    add_exit(WEST_R_DIR + "er19",   "south",0,2);
    add_exit(FROG_DIR + "inn",      "east");
/*  Scavenger hunt 2001
    add_exit(FROG_DIR + "inn1",      "east");
*/
    add_exit(FROG_DIR + "smial01", "west");
 
}
 
int
read_sign()
{
    write ("You see 'The Floating Log Inn' carved into the " +
        "sign.\n");
    say(QCTNAME(TP) + "reads the sign.\n");
    return 1;
}
