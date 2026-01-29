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

inherit BASE_ROAD;

void
create_road()
{
    add_prop(ROOM_S_MAP_FILE,"faerun_map.txt");

    set_short("a dusty old road");
    set_extraline("The grasslands stretch out in all directions as the road runs through it. Wildflowers and bushes dot the grassland.");

    reset_faerun_room();

    add_grasslands();
    add_highroad();

    add_exit(HR_DIR + "nrd09", "northwest");
    add_exit(HR_DIR + "nrd07", "south");

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
