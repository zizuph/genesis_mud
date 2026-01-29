/*
 * An underground shaft near the beach in Faerie
 * By Finwe, August 2004
 */

#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

inherit WATER_BASE;
inherit SEA_CAVE_BASE;

void
create_sea_cave_room()
{
    set_short("An underground shaft");
    set_long(short() + ". Water sprays up from an underground " +
        "spring. It looks like the shaft was probably full of water at " +
        "one time, but that is nolonger the case. The walls are irregular, " +
        "but too wet to climb. A rusty grate is at the top of " +
        "the shaft, allowing a little light down here. The water flows " +
        "to the east which is  probably the only way out of here.\n");
    
    add_item(({"shaft"}),
        "It is long and somewhat straight. It rises above you and is covered with a rusty grate.\n");
    add_item(({"grate", "grate"}),
        "It looks small from down here, but looks square. It covers the top of the shaft and allows some light to filter down here.\n");
    add_item(({"spring", "underground spring"}),
        "It is a large crack in the ground. Water sprays up from it, wetting the walls and everything else here.\n");
    add_item(({"crack"}),
        "It is irregularly shaped and very large. Water sprays up from it, partially filling the shaft.\n");
   
    set_add_stream();
    reset_room();

// sets drinking functions
    set_drink_from( ({ "river", "stream"}) );   
    add_prop(OBJ_I_CONTAIN_WATER, 1000000);  

    add_exit(FOREST_DIR + "river01", "east",0,3);

}

public void
init()
{
    ::init();
    init_drink();
}
