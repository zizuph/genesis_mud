/*
 * Corsair room
 *
 * Raymundo, June 2020
 */

#pragma strict_types

inherit "/d/Gondor/std/room";
inherit "/d/Gondor/common/lib/herbsearch";
inherit "/d/Gondor/tharbad/trail/base_room";
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

/* prototypes */
public void  create_gondor();


/*
 * Function name:    create_gondor
 * Description:      create the basic room
 */
void
create_gondor()
{
    set_short("On the edge of a clearing");

    set_long("Short trees, not much more than bushes really, line the "
        + "edges of the clearing, doing little to offer shade. However, "
        + "they are thick and difficult to peer through; this clearing "
        + "is likely safe from observers. The clearing stretches far to the "
        + "southeast.\n");

    add_landscape();
    add_cmd_item( ({"trees", "bushes", "through trees", "through bushes"}),
        "peer", "You try to peer through the trees but are unable to do "
        + "so.\n");

    add_exit("pathb", "northeast");
    add_exit("pathf", "east");
    add_exit("pathh", "southwest");
    add_exit("pathi", "southeast");

}   /* end create_gondor () */

