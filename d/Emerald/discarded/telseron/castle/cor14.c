
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
    add_my_desc("Large windows in the western wall " +
        "fill the room with light. The light reflects off the walls " +
        "filing the room with brilliance. North leads towards the " +
        "throne room, south goes to the King's guard room, east " +
        "goes into the Hall of Mirrors.\n\n");

    add_item(({"window", "windows"}),
        "The windows are expansive and fill the corridor with " +
        "light. They are arch shaped.\n");
    add_item(({"mirror"}),
        "The mirror is placed at a wierd angle so as not to show your "+
        "reflection, but to make the corridor seem longer than it "+
        "really is.\n");

    add_exit( TCASTLE_DIR + "cor12",  "north");
    add_exit( TCASTLE_DIR + "g_rm01", "south");
    add_exit( TCASTLE_DIR + "cor15", "east");
}

