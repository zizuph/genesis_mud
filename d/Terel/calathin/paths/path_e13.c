/*
    Standard path for the town of Calathin, in the Terel domain

    Based on Vader's original path room (path_n01.c). Mortricia 920723
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

#include <macros.h>
#include <stdproperties.h>


public void
create_room()
{
     set_short("A small path");

     set_long(
        "You are standing on a small path. Far north you catch a glimpse " +
        "of a river through the trees. The path continues " +
        "northeast and southwest. " +
        "A small track is going east.\n");

     add_item(({"tree", "trees"}), "These tall pines really do well in " +
        "this kind of climate. They are all covered with snow.\n");

     add_item(({"snow"}), "The snow reflects the sunlight off the top of " +
        "the trees, giving it a silver color.\n");

     add_item(({"path"}), "It's not that much beaten by shoes or wheels, " +
        "but the locals probably use it every now and then.\n");

     add_item(({"river", "water"}), "You don't see that much of the river " +
        "from your location.\n");

     add_exit(CALATHIN_DIR + "paths/path_e12", "northeast", 0);
     add_exit(CALATHIN_DIR + "paths/path_e14", "southwest", 0);
     add_exit(CALATHIN_DIR + "paths/track_s01", "east", 0);
}
