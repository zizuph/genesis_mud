#include "defs.h"
inherit ROAD_ROOM;
/* By Sarr */

void
create_room()
{
    ::create_room();
    set_short("On a dirt road in Drakmere");
    set_long("You are on a dirt road in the east part of the city of "+
    "Drakmere, where the residential area is. The road runs west and "+
    "east along the great south wall. Far to the west, you see a "+
    "stone keep rising out of the ground. A wooden house stands to "+
    "the north.\n");
    add_item(({"wooden house","house"}),"Probably owned by a resident "+
    "of Drakmere.\n");
    add_item(({"stone keep","keep"}),"It's probably where you can find "+
    "the Lord of Drakmere and the rest of the royalty at.\n");
    add_item(({"city wall","wall"}),"The great wall that protects the "+
    "city from the savages that lay outside. Guards patrol the tops, "+
    "keeping an eye out for trouble.\n");
    add_exit(DRAKMERE_DIR + "road43","east",0,0,0);
    add_exit(DRAKMERE_DIR + "road45","west",0,0,0);
    add_exit(DRAKMERE_DIR + "house15","north","@@house",0,0);
}

int
house()
{
    write("You creep quietly into the house.\n");
    return 0;
}

