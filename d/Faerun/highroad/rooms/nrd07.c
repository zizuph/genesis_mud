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

    set_short("an old stone road");
    set_extraline("Trees and bushes are cleared away from the road. The well travelled road runs nearly north and south and passes through grasslands.");

    reset_faerun_room();

    add_grasslands();
    add_highroad();

    add_exit(HR_DIR + "nrd08", "north");
    add_exit(HR_DIR + "nrd06", "southeast");
	
	//add_exit("/d/Faerun/sunken_ruins/rooms/forest", "west", 0,0,1);

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
