#include "defs.h"
inherit ROAD_ROOM;
/* By Sarr */

void
create_room()
{
    ::create_room();
    set_short("On a dirt road in Drakmere");
    set_long("You are on a dirt road in the north part of the city of "+
    "Drakmere, where the residential area of the city is. "+
    "A small wooden house stands to your west and east, while the road "+
    "leads south into the city center, and north to the great wall "+
    "that surrounds the city.\n");
    add_item("city center", "The city center where all activity is.\n");
    add_item(({"great wall","wall"}),"The great wall that protects the "+
    "city from the savages that lie outside. Guards patrol the tops, "+
    "keeping an eye out for trouble.\n");
    add_item("house","Probably owned by residents of Drakmere.\n");
    add_exit(DRAKMERE_DIR + "road01","north",0,0,0);
    add_exit(DRAKMERE_DIR + "road03","south",0,0,0);
}
