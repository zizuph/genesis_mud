/*
 * The High Road near the Mere
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
    set_extraline("The road looks well travelled. It is large and ancient " +
        "looking. It meanders past a large swamp, which looks dangerous. " +
        "The road is covered with large cobbles which are smooth from " +
        "constant traffic.");

    reset_faerun_room();

    add_grasslands();
    add_highroad();
    add_mere();
    add_std_herbs("mere");

    add_exit(HR_DIR + "srd03", "northwest");
    add_exit(HR_DIR + "srd05", "east");
    add_exit(ME_DIR + "me06", "southwest");
//    add_exit(ME_DIR + "me07", "southeast");

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
