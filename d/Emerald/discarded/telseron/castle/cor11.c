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
    add_my_desc("Large windows in the north and eastern wall fill " +
        "the room with light. The light reflects off the walls " +
        "filling the room with a brilliant aura. West leads towards " +
        "the throne room while south goes to the royal chambers.\n\n");

    add_item(({"window", "windows"}),
        "The windows are large and reach to the ceiling. They are " +
        "arch shaped and fill the corridor with light.\n");
 
    add_exit( TCASTLE_DIR + "cor13", "south");
    add_exit( TCASTLE_DIR + "cor10", "west");
}
