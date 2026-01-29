/*
 * Trail in the Grasslands near the High Road
 * -- Finwe, July 2006
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

#define WARLOCK_GUILD_DIR "/d/Faerun/guilds/warlocks/"

inherit BASE_ROAD;

void
create_road()
{
    add_prop(ROOM_S_MAP_FILE,"highroad_map.txt");
    set_short("an old stone road");
    set_extraline("The well-travelled road runs alongside a swamp. The " +
        "road runs across the grassland, which is covered with thick " +
        "grass. The swamp looks sickly and dangerous.");

    reset_faerun_room();

    add_grasslands();
    add_highroad();
    add_mere();
    add_std_herbs("mere");

    add_exit(HR_DIR + "srd07", "northwest");
    add_exit(HR_DIR + "srd09", "southeast");
    add_exit(ME_DIR + "me19", "southwest");
    
    // Questnpc for the find infant quest.
    add_npc(WARLOCK_GUILD_DIR + "npc/quest_woman", 1);
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


