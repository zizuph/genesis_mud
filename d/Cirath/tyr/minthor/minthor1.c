/* minthor1: Bogus room till minthor mansion is built. */

inherit "/std/room";
#include "defs.h"

void
create_room()
{
    set_short("minthor construction site");
    set_long("A massive swarm of slaves move stone and wood around in an "+
             "attempt to build some sort of mansion as swiftly as "+
             "possible. Their cruel taskmasker appears every so often to "+
             "beat those who falter.\n");

    add_item("taskmaster", "All the slaves will say is that his name is "+
             "Milashk.\n");
    add_item(({"slave", "slaves"}), "A pathetic wretch.\n");

    INSIDE

    add_exit(TZ_CARAVAN+"rd_cw_05.c", "south", 0, 1);
}
