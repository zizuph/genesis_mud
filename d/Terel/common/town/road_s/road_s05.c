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
        "The road continues to north and southeast.\n"));

    add_item(({"tree", "trees"}), BS("These pine trees are all tall and " +
        "straight. Perfect for building cabins and houses.\n"));

    add_item(({"snow"}), BS("The snow never disappears in this part of " +
        "the world. Here it's damn cold unless you have warm clothes.\n"));

    add_exit(TOWNDIR + "road_s/road_s04", "north", 0);
    add_exit(TOWNDIR + "road_s/road_s06", "southeast", 0);
}
