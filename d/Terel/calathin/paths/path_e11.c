/*
    Standard path for the town of Calathin, in the Terel domain

    Based on Vader's original path room (path_n01.c). Mortricia 920723
    modified by dust 920812: added property ROOM_HAS_WATER
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

#include <macros.h>
#include <stdproperties.h>


public void
create_room()
{
     set_short("A small wooden bridge");
     set_long(
        "You are standing on a small wooden bridge. You can go north " +
        "and south from here. There are some trees on both sides " +
        "of the river.\n");

     add_item(({"tree", "trees"}),"These tall pines really do well in " +
        "this kind of climate. They are all covered with snow.\n");

     add_item(({"snow"}), "The snow reflects the sunlight off the top of " +
        "the trees, giving it a silver color.\n");

     add_item(({"path"}), "It's not that much beaten by shoes or wheels, " +
        "but the locals probably use it every now and then.\n");

     add_item(({"bridge"}), "It's a simple looking wooden bridge. " +
        "It looks fairly robust though, and someone must quite regularily " +
        "maintain it.\n");

     add_item(({"river", "water"}), "The river looks very cold, and you " +
        "would not live very long if you fell into the water. " +
        "Every now and then a piece of ice floats by.\n");

     add_prop(ROOM_HAS_WATER, 1);
     add_exit(CALATHIN_DIR + "paths/path_e10", "north", 0);
     add_exit(CALATHIN_DIR + "paths/path_e12", "south", 0);

}
