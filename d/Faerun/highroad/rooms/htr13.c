/*
 * Mountain trail in the Sword Mountains
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
    add_prop(ROOM_S_MAP_FILE, "sword_mt_map.txt");

    set_short("a snowy trail");
    set_extraline("Snow drifts have accumulated everywhere in the mountains. They look like giants standing guard. The path is hidden beneath the snow, but it appears to run north and west.");

    add_item(({"trail", "snowy trail", "path"}),
        "The trail is barely visible and hidden by the snow, but it appears to run north and west.\n");
    
    reset_faerun_room();

    add_sword_mts_cold();

    add_exit(HR_DIR + "htr14", "north");
    add_exit(HR_DIR + "htr12", "west");


}

public void
init()
{
    ::init();
}

void
reset_faerun_room()
{
}

int climb()
{
    TP->move_living("climbing down the face of cliff.", HR_DIR + "htr08");
    return 1;
   
}