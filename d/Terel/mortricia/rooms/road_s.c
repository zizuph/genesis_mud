/*
    This is a standard east road. Mortricia 920723
 */

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Terel/common/terel_defs.h"

#define BS(message)     break_string(message, 70)

create_room()
{
    set_short("The south road");

    set_long(BS(
        "This icy road will take you to the southern parts of Calathin. " +
        "There are a few trees scattered around the road. " +
        "The road continues northwest and south. There is a small " +
        "path going north.\n"));

    add_item(({"tree", "trees"}), BS("These pine trees are all tall and " +
        "straight. Perfect for building cabins and houses.\n"));

    add_item(({"snow"}), BS("The snow never disappears in this part of " +
        "the world. Here it's damn cold unless you have warm clothes.\n"));

    add_item(({"path"}), BS("The path looks rather well-travelled.\n"));

    add_exit(TOWNDIR + "road_s/road_s06", "northwest", 0);
    add_exit(TOWNDIR + "paths/path_e14", "north", 0);
    add_exit(TOWNDIR + "road_s/road_s07", "south", "@@later");
}

later() {
    write(BS("The road to the southern wilderness is not yet completed. " +
        "Please, come back later.\n"));
    return 1;
}
