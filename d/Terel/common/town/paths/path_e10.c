/*
    Standard path for the town of Calathin, in the Terel domain

    Based on Vader's original path room (path_n01.c). Mortricia 920723
 */

inherit "/std/room";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Terel/common/terel_defs.h"

#define BS(message)       break_string(message, 70)

create_room()
{
    set_short("A small path");

    set_long(BS(
        "You are standing on a small path just north of the river. " +
        "There are trees, scattered " +
        "rather sparsely, on both sides of the path. The path continues " +
        "south over a small wooden bridge, and to the north " +
        "where it reaches a road.\n"));

    add_item(({"tree", "trees"}), BS("These tall pines really do well in " +
        "this kind of climate. They are all covered with snow.\n"));

    add_item(({"snow"}), BS("The snow reflects the sunlight off the top of " +
        "the trees, giving it a silver color.\n"));

    add_item(({"path"}), BS("It's not that much beaten by shoes or wheels, " +
        "but the locals probably use it every now and then.\n"));

    add_item(({"road"}), "It looks well travelled.\n");

    add_item(({"bridge"}), BS("It's a simple looking wooden bridge. " +
        "It looks fairly robust though, and someone must quite regularily " +
        "maintain it.\n"));

    add_item(({"river", "water"}), BS("The river looks very cold, and you " +
        "would not live very long if you fell into the water.\n"));

    add_exit(TOWNDIR + "road_e/road_e08", "north", 0);
    add_exit(TOWNDIR + "paths/path_e11", "south", 0);

}
