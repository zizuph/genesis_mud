/* rd_ds_02: Middle section of Diamond Street, 10/8/95. */
 
inherit "/std/room";
inherit "/d/Cirath/std/Cirath_magic_room_std";
#include "defs.h"


void
create_room()
{
    ::create_room();        
    set_short("Diamond Street center");
    set_long("At this spot Pandora's End stabs into the side of the "
            +"east-west running Diamond Street, intersecting in the "
            +"shadow of Tyr's mighty stone wall. South down the End you "
            +"can just make out a statue, which sits in front of the "
            +"hulking tower that serves as the city's jail. While the "
            +"sun beats down as brutally as ever, things seem muted so "
            +"close to the jail and slave pits. Even the awesome "
            +"Ziggurat seems less inspiring.\n");
 
    add_item(({"jail", "tower", "hulking tower"}),
             "Blotting out the bloated sun, this dark tower is "
            +"the final stop for many of Tyr's criminals and dissidents. "
            +"The lucky die before they ever near that place.\n");
    add_item(({"wall", "stone wall"}), "The thick structure has kept "
            +"Tyr marginally safe for much of Kalak's reign.\n");
    add_item("statue", "You can't make it out from this spot.\n");
 
    OUTSIDE
    ADD_SUN_ITEM
    ADD_ZIG_ITEM
 
    add_exit(TYR_NOBLE+"rd_ds_01.c", "west", 0, 1);
    add_exit(TYR_SLAVE+"rd_pe_03.c", "south", 0, 1);
    add_exit(TYR_SLAVE+"rd_ds_03.c", "east", 0, 1);
}
