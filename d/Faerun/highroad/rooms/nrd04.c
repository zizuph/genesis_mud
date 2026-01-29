/*
 * The Northern end of the High Road
 * -- Finwe, July 2006
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>
//#include "/d/Faerun/guilds/black_flame/guild.h"

inherit BASE_ROAD;

/*public int
block_player()
{
    if (BF_MASTER->is_lay_bf(this_player()->query_name()) == 1)
    {          
        return 0;
    }    
    
    write("While there is a wide road going in that "
    +"direction, you think it's best to not stray "
    +"too far from the highroad at this time. Maybe "
    +"later?\n");
    
    return 1;
}*/


void
create_road()
{
    add_prop(ROOM_S_MAP_FILE,"faerun_map.txt");

    set_short("an old stone road");
    set_extraline("Bushes and trees have been cleared away from the " +
        "road. The cobblestone road is well traveled. It runs "
        +"generally north and south through the grasslands. At some distance to "
        +"the northeast, you spot black smoke rising towards the sky and "
        +"some glint of fire through the bushes and trees in that "
        +"direction.");

    reset_faerun_room();

    add_grasslands();
    add_highroad();

    add_exit(HR_DIR + "nrd05", "north");
    //add_exit(HR_DIR + "temproad01", "northeast", block_player);
    add_exit(HR_DIR + "nrd03", "southeast");

}

public void
init()
{
    ::init();
}

void
reset_faerun_room()
{
    set_searched(0);
}
