#include "defs.h"
inherit ROAD_ROOM;
/* By Sarr */

object guard;
void reset_room();

void
create_room()
{
    ::create_room();
    set_short("On a dirt road in Drakmere");
    set_long("The dirt road ends here at the corner of the north "+
    "and west stone walls. The road leads east through the "+
    "residential area, and south through a grassy field.\n");
    add_item(({"grassy field","field"}),"A beautiful green field of "+
    "grass and flowers. You see children playing around.\n");
    add_item("flowers","Red, purple, blue, and yellow flowers dot the "+
    "entire area.\n");
    add_item("children","They are playing around among the flowers and "+
    "beautiful green grass hills.\n");
    add_item(({"walls","stone walls"}),"They protect the city from the "+
    "savages that lay waiting outside in the darkness. You see a few "+
    "guards walking around the tops, patroling.\n");
    reset_room();
    add_exit(DRAKMERE_DIR + "road28","east",0,0,0);
    add_exit(DRAKMERE_DIR + "road26","south",0,0,0);
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

