#include "defs.h"
inherit ROAD_ROOM;
/* By Sarr */

void
create_room()
{
    ::create_room();
    set_short("On a dirt road in Drakmere");
    set_long("You are on a dirt road in the east part of the city of "+
    "Drakmere. To the west, the city center lies, while to the east, "+
    "the road continues until it hits the east wall of the city.\n");
    add_item("wall","The great wall that surrounds the entire city "+
    "to protect it from the savages that lurk outside.\n");
    add_exit(DRAKMERE_DIR + "road21","east",0,0,0);
    add_exit(DRAKMERE_DIR + "road19","west",0,0,0);
}
