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
    "square. A large building is off to your east, while to the "+
    "west, you see a small, dark building where you hear hammering "+
    "noises.\n");
    add_item("gates","The gates are off to the south.\n");
    add_item("buildings","The west or east one?\n");
    add_item("west building","It looks like a smithy.\n");
    add_item("east building","It looks like an inn or tavern.\n");
    add_exit(DRAKMERE_DIR + "road07","north",0,0,0);
    add_exit(DRAKMERE_DIR + "road09","south",0,0,0);
}
