#include "defs.h"
inherit ROAD_ROOM;
/* By Sarr */

void
create_room()
{
    ::create_room();
    set_short("On a dirt road in Drakmere");
    set_long("You are on dirt road that heads north through a large "+
    "grassy field. There air here smells fresh and clean, as flowers "+
    "pop out of the ground along the fields, perfuming the air. You "+
    "are now close to the walls. The road ahead turns east through "+
    "what looks like a residential area. There is a little wooden "+
    "house to your east.\n");
    add_item(({"wooden house","house"}),"It looks like someone's "+
    "home.\n");
    add_item(({"grassy field","field"}),"A beautiful green field of "+
    "grass and flowers. You see children playing around.\n");
    add_item("flowers","Red, purple, blue, and yellow flowers dot the "+
    "entire area.\n");
    add_item("children","They are playing around among the flowers and "+
    "beautiful green grass hills.\n");
    add_item(({"walls","stone walls"}),"They protect the city from the "+
    "savages that lay waiting outside in the darkness. You see a few "+
    "guards walking around the tops, patroling.\n");
    add_exit(DRAKMERE_DIR + "road27","north",0,0,0);
    add_exit(DRAKMERE_DIR + "road25","south",0,0,0);
}
