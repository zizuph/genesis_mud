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
    add_my_desc("Large windows in the eastern wall fill the " +
        "room with light. The light reflects off the walls filling " +
        "the room with a brilliant aura. \n\n");

    add_item(({"window", "windows"}),
        "The windows are expansive and fill the corridor with " +
        "light. They are arch shaped.\n");

    add_exit( TCASTLE_DIR + "cor11", "north");
    add_exit( TCASTLE_DIR + "cor20", "south");
}
