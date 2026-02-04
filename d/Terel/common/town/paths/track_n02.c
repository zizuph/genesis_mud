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
        "You are standing on a track. There are quite a few trees around. " +
        "The track continues southwest and east.\n"));

    add_item(({"tree", "trees"}), BS("These tall pines really do well in " +
        "this kind of climate. They are all covered with snow.\n"));

    add_item(({"snow"}), BS("The snow reflects the sunlight off the top of " +
        "the trees, giving it a silver color.\n"));

    add_item(({"track"}), BS("It's a small track, but it appears to be used " +
        "every now and then.\n"));

    add_exit(TOWNDIR + "paths/track_n01", "southwest", 0);
    add_exit(TOWNDIR + "paths/track_n03", "east", 0);
}
