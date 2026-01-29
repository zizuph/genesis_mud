/*
 * G3.c
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
    set_em_long("The strange path follows the course of a giant, "+
        "gray stone wall in a meandering north/south path. The wall's "+
        "high-reaching top is concealed by the unnatural darkness "+
        "that blankets this entire area. The eastern side of the "+
        "path is bordered by the edge of a leafless forest populated "+
        "by thick, white-barked trees.\n");

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

    add_exit(AVMAIN+"g0", "north");
    add_exit(AVMAIN+"g4", "southeast");
}
