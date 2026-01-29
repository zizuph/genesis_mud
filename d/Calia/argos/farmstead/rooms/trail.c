/* /d/Calia/argos/farmstead/rooms/trail.c
**   A trail leading from Argos to the farmstead area
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   2/21/20    Brine      Created
**
*/

#pragma strict_types

inherit  "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

void
create_room()
{
    seteuid(getuid());

    set_short("An overgrown forest trail");

    set_long(
        "You are standing on an old, overgrown trail in a mixed forest. "
        + "Tall oaks and maple trees grow all around you, and dense "
        + "undergrowth makes the areas surrounding the trail practically "
        + "impassable. Alpharon road lies to the southwest, while to the "
        + "north the trail slopes up towards a large clearing.\n"
    );

    add_item(
        ({ "slope", "clearing" }),
        "A large clearing lies atop a slope to the north.\n"
    );

    add_item(
        ({
            "trail", "path", "weed", "weeds", "grass", "old trail",
            "overgrown trail", "old, overgrown trail", "forest trail",
            "overgrown forest trail", "weeds and grass"
        }),
        "The trail is overgrown with weeds and grass, but is still easily "
        + "traveled. At some point it was wide enough for a cart, but now "
        + "it's just a little wider than an animal trail.\n"
    );

    add_item(
        ({
            "trees", "forest", "mixed forest", "woods", "wooded area",
            "maples", "oaks", "maple trees", "oak trees", "area", "oak",
            "maple", "tall oaks"
        }),
        "A mix of maple trees and oaks grow to form a forest on both sides "
        + "of the trail. To the west they seem to grow more sparsely.\n"
    );

    add_item(
        ({ "road", "alpharon road" }),
        "Alhparon road lies to the southwest.\n"
    );

    add_item(
        ({
            "undergrowth", "dense undergrowth", "shrub", "shrubs", "dense "
            + "shrubs", "plants", "other plants"
        }),
        "Shrubs and other plants form a dense undergrowth between the trees, "
        + "making travel outside of the trail impossible.\n"
    );

    add_exit(ROOM_DIR + "aroad18", "southwest");
    add_exit(ROOM_DIR + "farmyard", "north");
}
