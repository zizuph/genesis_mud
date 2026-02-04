/*
    Stadard track for the town of Calathin, in the Terel domain

    Based on Vader's original path room (path_n01.c). Mortricia 920723
    Updated by Shinto 103199
*/

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

#include <macros.h>
#include <stdproperties.h>

object gate;

public void
create_room()
{
    set_short("A track");

    set_long(
        "You are standing on a track just outside a farm. There are some " +
        "fields around you. You can go east through the gate to the " +
        "farmyard or go west on the path.\n");

    add_item(({"gate","fence"}),
        "Standard split-rail designed fence separates the rest of the " +
        "world from the farm. The gate seems to be the only proper way " +
        "through.\n");

    add_item(({"track"}), "It's a small track, but it appears to be used " +
        "every now and then.\n");

    add_item(({"farm"}), "The farm consists of three separate " +
        "houses, placed around a farmyard.\n");

    add_item(({"field", "fields"}), "The fields are now covered" +
        " with snow, but still, some kind of rye grow there.\n");

    add_item(({"snow"}), "It's pure snow.\n");

    add_item(({"rye"}), "This kind of rye must be quite tough " +
        "since it endures this harsh climate.\n");

    add_exit(CALATHIN_DIR + "paths/track_n03", "west", 0);

    gate = clone_object(CALATHIN_DIR + "farms/obj/farm2_gate");
    gate->move(TO);
}
