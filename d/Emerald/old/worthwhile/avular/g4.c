/*
 * G4.c
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
    set_em_long("The path here is brought up short by an enclosing arm "+
        "of the forest edge. The forest is populated by large, white-"+
        "barked, leafless trees, disappearing into the darkness to the "+
        "east. The west side of the path is bordered by a massive, gray "+
        "stone wall. The amazingly smooth, carved wall extends upward "+
        "to a point high above hidden the by the encompassing darkness.\n");

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

    add_exit(AVMAIN+"g3", "northwest");
}
