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
    set_extraline("Snow covers the trail, hiding it from view, but it looks like it heads north and southwest. It passes by snow drifts. They tower overhead and hide everything here. Bright " + CLOCK->query_light_type() + " reflects off the snow drifts.");

    add_item(({"trail", "rocky trail", "path"}),
        "The trail is hidden from view by all the snow here but appears to run north, southwest, and after "
        +"closer inspection, also to the east towards the base of the mountain.\n");
    
    reset_faerun_room();

    add_sword_mts_cold();

    add_exit(HR_DIR + "htr11", "north");
    add_exit("/d/Faerun/guilds/fire_knives/rooms/mountain_ft", "east",0,0,1);
    add_exit(HR_DIR + "htr09", "southwest");


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