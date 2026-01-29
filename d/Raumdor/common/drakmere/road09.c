#include "defs.h"
inherit ROAD_ROOM;
/* By Sarr */

void
create_room()
{
    ::create_room();
    set_short("South dirt road in Drakmere");
    set_long("You now stand in the middle of a small dirt and stone "+
    "road that leads south to the city gates and north to the city "+
    "square. Off to the west you see a huge stone keep, where the "+
    "royalty live.\n");
    add_item("keep","Probably where the Lord of Drakmere and his followers "+
    "reside.\n");
    add_item("gates","The gates are off to the south.\n");
    add_exit(DRAKMERE_DIR + "road08","north",0,0,0);
    add_exit(DRAKMERE_DIR + "road10","south",0,0,0);
}
