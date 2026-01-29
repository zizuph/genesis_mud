/* rd_ds_03: Mid eastern section of Diamond Street, 10/16/95. */
 
inherit "/std/room";
#include "defs.h"
 
void
create_room()
{
    set_short("diamond Street east");
    set_long("Winding its way between the northern wall of the Jail of "
            +"Tyr and the mighty stone wall that protects the city, the "
            +"street known as Diamond poorly lives up to its name. Rather "
            +"then being filled with oppulance, the edges of the road "
            +"are empty and the people bereft of hope. From the "
            +"southeast echo the cries of tormented slaves, many of "
            +"whom are working on the Ziggurat. Just to the north "
            +"is a small building with an obsidian club hanging above "
            +"the entry.\n");
 
    add_item(({"club","building","entry","small building","dust"}),
             "Black dust drifts from its doorway.\n");
 
    add_item(({"jail", "jail of tyr"}),
             "Blotting out the bloated sun, this dark tower is "
            +"the final stop for many of Tyr's criminals and dissidents. "
            +"The lucky die before they ever near that place.\n");
    add_item(({"wall", "stone wall"}), "The thick structure has kept "
            +"Tyr marginally safe for much of Kalak's reign.\n");
 
    OUTSIDE
    ADD_SUN_ITEM
    ADD_ZIG_ITEM
 
    add_exit(TYR_SLAVE+"obsdmrch.c", "north", 0, 1); 
    add_exit(TYR_SLAVE+"rd_ds_02.c", "west", 0, 1);
    add_exit(TYR_SLAVE+"rd_ds_04.c", "southeast", "@@smell_message", 1);
}
 
public int
smell_message()
{
    TP->catch_msg("You smell something ghastly up ahead.\n");
    return 0;
}
