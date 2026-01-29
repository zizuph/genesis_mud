/*
 * Trail in the hills near the High Road
 * -- Finwe, July 2006
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

//inherit HIGH_RD_DIR + "std/base_road.c";
inherit BASE_ROAD;

void
create_road()
{
    add_prop(ROOM_S_MAP_FILE, "sword_mt_map.txt");

    set_short("a rocky trail");
    set_extraline("The rocky trail ends here at the face of the hills. Rocks are scattered everywhere as well as boulders. A large cave opens to the east.");

    add_item(({"cave"}),
        "It is a large, irregular opening in the mountain. The cave is " +
        "dark and foreboding. A musty smell drifts from it.\n");

    add_item(({"trail", "rocky trail", "path"}),
        "The trail is a thin line that wanders through the mountains. It " +
        "is littered with rocks which hide it from casual travellers.\n");
    add_item(({"face", "face of the hills", "cliff"}),
        "The face of the hill has been sheared off by some cataclysmic force. It has vertical ridges in it from where the hill was split off and fell away.\n");
    add_item(({"ridges", "vertical ridges"}),
        "They are rough looking and run the length of the cliff. It looks like you could probably climb them.\n");
    
    reset_faerun_room();

    add_sword_mts1();

    add_exit("/d/Faerun/underdark/dark_dom/rooms/cv01", "east");
    add_exit(HR_DIR + "htr07", "west");


    add_cmd_item(({"up", "cliff", "face", "ridges"}),"climb","@@climb");
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
    if(TP->query_skill(SS_CLIMB)>20)
    {
        TP->move_living("climbing up the face of the cliff.", HR_DIR + "htr09");
        return 1;
    }

    if(TP->query_skill(SS_CLIMB)>10)
    {
        TP->catch_msg("You almost manage to climb up, but it is a little too hard for you.\n");
        return 1;
    }

    TP->catch_msg("You are not skilled enough to climb up.\n");
    return 1;
}