/*
 * The North end of the High Road
 * -- Finwe, December 2015
 *
 *added exit to rogue camp
 *--Clyptas, August 2017
 *
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit BASE_ROAD;

string rd_descr = "";
void
create_road()

{    
    add_prop(ROOM_S_MAP_FILE,"faerun_map.txt");
    set_short("a dusty old road");
    set_extraline(nrd_desc3(rd_descr));

    reset_faerun_room();

    add_grasslands();
    add_highroad();
    add_std_herbs("meadow");

    add_exit(HR_DIR + "nrd24", "north");
    add_exit(HR_DIR + "nrd22", "southeast");
    add_exit("/d/Faerun/menzo/rooms/camp/menzo_start", "east");
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
