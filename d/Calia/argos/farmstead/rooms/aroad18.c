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

    set_short("Alpharon Road through a forest");
    set_long("You stand on Alpharon road. Maple trees and oaks rise to the "
    + "north and south, providing some shade. The road runs east to west, "
    + "while an overgrown trail leads to the northeast.\n");

    add_item(
      ({ "road", "street", "alpharon road" }),
      "Alpharon road runs east and west here. To the east it seems to be "
      +"blocked off by a fallen tree.\n"
    );

    add_item(
      ({
        "trees", "forest", "mixed forest", "woods", "wooded area",
        "maples","oaks", "maple trees", "oak trees", "area", "oak", "maple"
      }),
      "A mix of maples and oaks grow to form a forest on both sides of "
      + "the road. To the west, they seem to grow more sparsely.\n"
    );

    add_item(
      ({ "tree", "fallen tree", "trunk", "large tree", "large fallen tree" }),
      "A large tree has fallen over the road to the east, its trunk blocking "
      + "any passage.\n"
    );

    add_item("shade", "The trees provide some shade.\n");

    add_item(
      ({"trail","overgrown trail"}),
      "An overgrown trail leads further into the forest to the northeast.\n"
    );

    add_exit(ROOM_DIR + "aroad17", "west", 0);
    add_exit(ROOM_DIR + "aroad18", "east", "@@closed");
    add_exit(ROOM_DIR + "trail", "northeast", 0);
}

int
closed()
{
    write("A large tree has fallen over the road to the east, its trunk "
    + "blocking any passage.\n");
    return 1;
}
