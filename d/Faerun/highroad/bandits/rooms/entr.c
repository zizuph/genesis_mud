/*
 * Bandit cave entrance
 * -- Finwe, July 2006
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit BASE_CAVE;

void
create_cave()
{
    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_ALLOW_STEED,1);
    set_short("a large cave");
    set_long("This is the inside of a large cave. It looks dirty from " +
        "garbage strewn everywhere. The garbage comes from bandits who " +
        "live here. The ceiling is low and the walls rough. There are " +
        "tunnels leading off away from here.\n");

    add_exit(CAVE_DIR + "start", "northwest");
    add_exit(CAVE_DIR + "train", "west");
    add_exit(CAVE_DIR + "shop", "south");
    add_exit(HR_DIR   + "btr03", "east");


}
