/* Road to Haven by Morrigan */

#include "/d/Krynn/haven/local.h"

inherit MOUNTBASE;

#define SOLACE_ROAD "/d/Krynn/darkenwd/road/road9"

void
create_mountain()
{
    add_my_desc("This area of the road is known as Sentinel Gap. "+
      "To the west the path ascends between the Twin peaks, and "+
      "it also continues eastwards.\n");

    add_exit(RDIR + "mount_road2", "west", "@@mountains", 3);
    add_exit(SOLACE_ROAD, "east");

    OUTSIDE;
}

int
mountains()
{
    write("You ascend into the pass between Twin Peaks.\n");
    return 0;
}

