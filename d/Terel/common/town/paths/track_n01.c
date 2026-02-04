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
        "By going west you go back on the path, northeast will take you " +
        "further " +
        "away from it.\n"));

    add_item(({"tree", "trees"}), BS("These tall pines really do well in " +
        "this kind of climate. They are all covered with snow.\n"));

    add_item(({"snow"}), BS("The snow reflects the sunlight off the top of " +
        "the trees, giving it a silver color.\n"));

    add_item(({"path"}), BS("It's not that much beaten by shoes or wheels, " +
        "but the locals probably use it every now and then.\n"));

    add_item(({"track"}), BS("It's a small track, but it appears to be used " +
        "every now and then.\n"));

    add_exit(TOWNDIR + "paths/path_e04", "west", 0);
    add_exit(TOWNDIR + "paths/track_n02", "northeast", 0);
}
