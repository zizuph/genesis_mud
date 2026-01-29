/*
 * The High Road
 * -- Finwe, July 2006
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit BASE_ROAD;

void
create_road()
{
    add_prop(ROOM_S_MAP_FILE,"highroad_map.txt");

    set_short("an old stone road");
    set_extraline("The road leads into hills to the west and heads " +
        "south across grasslands. Northeast are the mountains locals " +
        "call the Sword Mountains.");

    reset_faerun_room();

    add_highroad();
    add_hills();
    add_sword_mts();
    add_std_herbs("hills");

    add_exit(HR_DIR + "srd13", "west");
    add_exit(HR_DIR + "srd15", "southeast"); 

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

