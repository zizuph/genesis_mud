/* /d/Calia/argos/farmstead/rooms/aroad17.c
**   ARGOS - farmstead - Alpharon road
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   2/21/20    Brine*      Created
**
**
**   * Adapted from aroom template from the metro area made
**     by Zima
*/
/* inherits/includes */

#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

void
create_room()
{
    seteuid(getuid());

    set_short("Alpharon Road through a wooded area");

    set_long("You stand on Alpharon road. Maples and oaks rise to the north "
        + "and south, providing some shade. The trees grow more densely "
        + "along the road to the east, and to the west an intersection marks "
        + "the entrance to the city of Argos.\n");

    add_item(({ "road", "street", "alpharon road" }),
        "Alpharon road runs east and west here.\n");

    add_item(
      ({
        "entrance", "entrance to argos", "entrance to the city of argos",
        "city", "argos", "city of argos", "intersection"
      }),
      "The city of Argos lies to the west.\n"
    );

    add_item("shade", "The trees provide some shade.\n");

    add_item(
      ({
        "tree", "trees", "forest", "mixed forest", "woods", "wooded area",
        "maples", "oaks", "maple trees", "oak trees", "area", "oak", "maple"
      }),
      "A mix of maples and oaks grow to form a wooded area on both sides of "
      + "the road. To the east they grow more densely, forming a forest.\n"
    );

    add_exit("/d/Calia/argos/metro/rooms/aroad16",  "west", 0);
    add_exit(ROOM_DIR + "aroad18",  "east", 0);
}
