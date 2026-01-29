/*
 * G1.c
 * Part of a path leading along the outside of the gates of
 * Avular.
 * - Alaron JAN 2000
 */

#include "defs.h"
#include <stdproperties.h>

inherit AVULAR_ROOM;

void
create_avular_room()
{
    set_short("A dark path");
    set_em_long("The path here is staggered and inconsistent. At some "+
        "points it is a straight line of worn earth, and at others "+
        "it is completely covered with odd, white grass. Along the "+
        "west side of the path, barely visible in the stifling darkness "+
        "is a huge, gray stone wall. The top of the wall is concealed "+
        "by the blackness. On the east side of the path, the edge of "+
        "a strange, leafless forest is barely visible.\n");

    add_item( ({"wall", "stone wall", "gray wall", "gray stone wall"}),
        "The stone wall is extremely smooth. In fact, it is far "+
        "smoother than any tool you know of could have made it. Running "+
        "your hand along the wall, you can't feel a single bump in the "+
        "cold, gray stone.\n");

    add_item( ({"wood", "woods", "forest", "leafless forest", "edge",
                "forest edge"}),
        "You can barely make out the edge of what in any other place "+
        "might have been a forest. Here, in the neverending darkness, "+
        "it is a forest of towering, white-barked, leafless trees. You "+
        "can't see any more of the forest than the very edge from here.\n");

    add_exit(AVMAIN+"g2", "north");
    add_exit(AVMAIN+"g0", "southwest");
}
