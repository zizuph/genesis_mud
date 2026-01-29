/*
 * G2.c
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
    set_em_long("The path here comes to an abrupt stop. The north and "+
        "east sides of the path are blocked by the edge of a strange, "+
        "leafless forest of tall, white-barked trees. A huge, gray "+
        "stone wall follows the west side of the path, and then recedes "+
        "into the darkness to the north and west. The path here is "+
        "mostly worn, dry ground with a few patches of the white "+
        "grass that seems to grow wild in this area. The cold touch of the "+
         "wind that blows through most of the area seems less icy here.\n");

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

    add_exit(AVMAIN+"g1", "south");

    clone_object(AV_OBJ+"mheater")->move(this_object());
}
