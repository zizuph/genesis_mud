/*
 * /d/Sparkle/area/faerie/rooms/orchard/orchard10.c
 *
 * The orchard of Faerie
 * By Finwe, September 1999
 */
 
#include "defs.h"
 
inherit ORCHARD_BASE;
 
void
create_orchard_room()
{
    //add_my_desc("\n");
    add_exit(ORCHARD_DIR + "orchard03", "north");     
    add_exit(GO_DIR + "road02", "south");
    add_exit(ORCHARD_DIR + "orchard11", "east");
    add_exit(ORCHARD_DIR + "orchard09", "west");

    add_std_herbs("forest");

    reset_room();
}

void reset_room()
{
    ::reset_room;
    set_searched(0);
    fruit_counter = 0;
}
