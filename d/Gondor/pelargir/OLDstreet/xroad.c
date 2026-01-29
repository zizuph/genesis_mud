#pragma strict_types

inherit "/d/Gondor/std/room.c";
inherit "/d/Gondor/pelargir/city_items.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_gondor()
{
    set_short("among a small cluster of houses");
    set_long(BSN("The street comes to a dead end a little east of "
        + "here. Small buildings line the street to both sides, and "
        + "the magnificent white tower of the Admiral, who rules in "
        + "Pelargir, rises above the houses to the south."));

    add_item( ({"buildings", "houses", }), BSN("Most of the houses "
        + "are in poor repair and seem to be derelict. To the north, "
        + "it is possible to enter a house through an open door, to "
        + "the south is an abandoned workshop."));
    add_admiral("south");
    add_item(({"door","house"}), "The open door of this "+
          "house seems to have been badly battered.\n");
    add_item( ({ "workshop", }), BSN("The building south of the "
        + "street probably was the workshop of a craftsman before "
        + "it was abandoned. You can still see the place over the "
        + "door where a sign was inviting customers, but the sign "
        + "is missing."));
    add_item( ({ "sign", }), "It is missing. Gone. Not here. You "
        + "cannot look at it.\n");

    add_exit(PELAR_DIR + "homes/ranhome",  "north", 0);
    add_exit(PELAR_DIR + "street/xroad1",  "east",  0);
    add_exit(PELAR_DIR + "homes/abanshop", "south", 0);
    add_exit(PELAR_DIR + "street/groad3",  "west",  0);
}
