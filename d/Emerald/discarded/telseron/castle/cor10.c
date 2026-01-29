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
    add_my_desc("A large crystal chandelier hangs from the " +
        "ceiling, filling the room with light. The light reflects " +
        "off the walls filling the room with a brilliant aura. " +
        "North leads to a corridor, west takes you into the King's " +
        "audience room, and east goes further into the castle.\n\n");
    
    add_item("chandelier",
        "The chandelier is enormous. It's multi-tiered and covered " +
        "with diamonds. Candles burn brightly, filling the " +
        "room with light. The diamonds move slightly, catching the " +
        "candlelight and throwing it onto the walls in a " +
        "rainbow of patterns.\n");
  
    add_exit( TCASTLE_DIR + "cor07", "north");
    add_exit( TCASTLE_DIR + "cor11",  "east");
    add_exit( TCASTLE_DIR + "ac01",  "west");
}
