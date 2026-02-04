/*
    Stadard track for the town of Calathin, in the Terel domain

    Based on Vader's original path room (path_n01.c). Mortricia 920723
 */

inherit "/std/room";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Terel/common/terel_defs.h"

#define BS(message)       break_string(message, 70)

create_room()
{
    set_short("A track");

    set_long(BS(
        "You are standing on a track just outside a farm. There are some " +
        "fields around you. You can go east to the farmyard or go west on " +
        "the path.\n"));

    add_item(({"track"}), BS("It's a small track, but it appears to be used " +
        "every now and then.\n"));

    add_item(({"farm"}), BS("The farm consists of three separate " +
        "houses, placed around a farmyard.\n"));

    add_item(({"field", "fields"}), BS("The fields are now covered" +
        " with snow, but still, some kind of rye grow there.\n"));

    add_item(({"snow"}), BS("It's pure snow.\n"));

    add_item(({"rye"}), BS("This kind of rye must be quite tough " +
        "since it endures this harsh climate.\n"));

    add_exit(TOWNDIR + "paths/track_n03", "west", 0);
    add_exit(TOWNDIR + "farms/yard_n", "east", 0);
}
