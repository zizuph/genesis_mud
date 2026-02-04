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
        "You are in the outskirts of a town standing on a road that will " +
        "take you eastwards. South of the road there is a river.\n"));

    add_item(({"tree", "trees"}), BS("These pine trees are all tall and " +
        "straight. Perfect for building cabins and houses.\n"));

    add_item(({"snow"}), BS("The snow never disappears in this part of " +
        "the world. Here it's damn cold unless you have warm clothes.\n"));

    add_item(({"river", "water"}), BS("The river streams fast, otherwise " +
        "it would have been covered with an ice layer. The water is real " +
        "cold.\n"));

    add_exit(TOWNDIR + "square1_4", "northwest", 0);
    add_exit(TOWNDIR + "road_e/road_e02", "southeast", 0);
}
