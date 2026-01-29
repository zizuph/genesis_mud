#include "defs.h"
inherit ROAD_ROOM;
/* By Sarr */

object guard;
void reset_room();

void
create_room()
{
    ::create_room();
    set_short("South dirt road in Drakmere");
    set_long("You stand in the middle of a dirt crossroads. To the west "+
    "lies a short road through a beautiful green courtyard to the royal "+
    "keep of Drakmere. To the south, the gates of the city stand, and to the east, "+
    "a small dirt road leads off into a residential area.\n");
    add_item("courtyard","It is filled with beautiful flowers and green "+
    "grass.\n");
    add_item("keep","Probably where the Lord of Drakmere and his followers "+
    "reside.\n");
    add_item("gates","The gates are off to the south.\n");
    reset_room();
    add_exit(DRAKMERE_DIR + "road09","north",0,0,0);
    add_exit(DRAKMERE_DIR + "road11","south",0,0,0);
    add_exit(DRAKMERE_DIR + "road48","west",0,0,0);
    add_exit(DRAKMERE_DIR + "road47","east",0,0,0);
}

void
reset_room()
{
    if(!guard)
    {
        guard = clone_object(DRAKMERE_NPC_DIR + "dguard");

        guard->move_living("xxx",TO);
    }
}

