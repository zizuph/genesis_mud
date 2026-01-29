/*
 * Citadel in the Kryptgarden
 * -- Finwe, August 2007
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit BASE_CITADEL;

#define MAX_NPCS 3

static object *npc = allocate(MAX_NPCS);

void
create_citadel()
{
    INDOORS;
    NO_STEEDS;
    set_short("Center of the Citadel");
    set_extraline("This is the third floor and it is large. It is made " +
        "of stone blocks and is round and deserted. A stone staircase " +
        "runs around the wall and leads down. The room looks like it " +
        "was recently visited but now looks deserted.");

    reset_faerun_room();
    set_add_citadel_out();

    add_item(({"stairs", "staircases"}),
        "The staircases runs around the wall. One set use to leads upstairs, " +
        "but that looks impossible now. The stairs are nothing more " +
        "than old stone blocks that extended out from the wall. They " +
        "are cracked and broken, but still allow visitors to go downstairs.\n");
    
    add_exit(CIT_DIR + "cit_3a", "north");
    add_exit(CIT_DIR + "cit_3c", "south");
    add_exit(CIT_DIR + "cit_3d", "east");
    add_exit(CIT_DIR + "cit_3b", "west");
    add_exit(CIT_DIR + "cit_2x", "down");
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
