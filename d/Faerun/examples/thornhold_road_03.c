/*
 * Road to Thornhold
 * -- Twire/Gnim June 2016
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit BASE_ROAD;

#define MAX_NPCS 3
#define GUARD_NPC    NPC_DIR + "guard"

static object *npc = allocate(MAX_NPCS);

void
create_road()
{
    add_prop(ROOM_S_MAP_FILE, "thornhold_road_map.txt");
    set_short("The road to Thornhold");
    set_extraline("The thin path runs through the grassland. It winds " +
        "around bushes and is hard to follow. It runs generally east " +
        "and southwest.");
    
    add_path();
    add_grasslands();
    add_std_herbs("meadow");

    reset_faerun_room();

    add_exit(ROOM_DIR + "thornhold_road_02",   "east");
    add_exit(ROOM_DIR + "thornhold_road_04",   "southwest");
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
