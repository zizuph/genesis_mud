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
   set_short("The east road");

    set_long(BS(
        "This icy and snowy road will take you eastwards. There are some " +
        "trees here and there. Just south of the road there is a river. " +
        "A small path is going northeast.\n"));

    add_item(({"tree", "trees"}), BS("These pine trees are all tall and " +
        "straight. Perfect for building cabins and houses.\n"));

    add_item(({"snow"}), BS("The snow never disappears in this part of " +
        "the world. Here it's damn cold unless you have warm clothes.\n"));

    add_item(({"river", "water"}), BS("The river streams fast, otherwise " +
        "it would have been covered with an ice layer. The water is real " +
        "cold.\n"));

    add_exit(TOWNDIR + "road_e/road_e04", "west", 0);
    add_exit(TOWNDIR + "road_e/road_e06", "east", 0);
    add_exit(TOWNDIR + "paths/path_e09", "northeast", 0);
}
