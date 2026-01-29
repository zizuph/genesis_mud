#include "defs.h"

inherit MIST_ROCK_BASE;

public void
create_mist_rock_room()
{
    add_mist_exit(TSHORE_EXIT | LROCK_EXIT,
        MIST_TOWER_DIR + "mist_isle25", "west");
    add_mist_exit(TSHORE_EXIT | RROCK_EXIT,
        MIST_TOWER_DIR + "mist_isle23", "southeast");
    add_mist_exit(TSHORE_EXIT, MIST_TOWER_DIR + "mist_isle22", "south");
    add_mist_exit(TSHORE_EXIT, MIST_TOWER_DIR + "mist_isle21", "southwest");

    add_exit("prominence01", "up", mist_block, 0, mist_nonobvious);
}

public string
cliff_desc()
{
    if (CAN_SEE_TOWER(this_player()))
    {
        return "The large, rock prominence looms approximately twenty " +
            "meters above you.  The sheer face of the cliff is clearly " +
            "unclimbable, but a steep, narrow passage, leading up to the " +
            "top, has been cut into the rock.  The top portion of a dark " +
            "tower is visible beyond the edge of the cliff wall.\n";
    }

    return "In the dense fog, it is impossible to see more than a few " +
        "feet of the cliff wall.  The face of the cliff seems unclimbable.\n";
}
