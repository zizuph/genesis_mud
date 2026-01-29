#include "defs.h"
inherit ROAD_ROOM;
/* By Sarr */

void
create_room()
{
    ::create_room();
    set_short("On a dirt road in Drakmere");
    set_long("You are on a dirt road in the east part of the city of "+
    "Drakmere, where the residential area is. The road runs north and "+
    "south along the east city wall.\n");
    add_item(({"city wall","wall"}),"The great wall that protects the "+
    "city from the savages that lie outside. Guards patrol the tops, "+
    "keeping an eye out for trouble.\n");
    add_exit(DRAKMERE_DIR + "road38","north",0,0,0);
    add_exit(DRAKMERE_DIR + "road21","south",0,0,0);
}
