/*
 * Corridor in castle of Telseron
 * By Finwe, November 1996
 */

inherit "/d/Emerald/telseron/castle/cor_base.c";
 
#include "/d/Emerald/defs.h"
#include "default.h"
 
void
create_corridor()
{
    add_my_desc("Large windows in the northern and western wall " +
        "fill the room with light. The light reflects off the walls " +
        "filing the room with brilliance. East leads into the music " +
        "room, south goes into the castle.\n\n");

    add_item(({"window", "windows"}),
        "The windows are expansive and fill the corridor with " +
        "light. They are arch shaped.\n");


    add_exit( TCASTLE_DIR + "cor06",      "south");
    add_exit( TCASTLE_DIR + "music_room", "east");
}
