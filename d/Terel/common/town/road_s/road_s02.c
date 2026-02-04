/*
    This is a standard east road. Mortricia 920723
    Modified by dust 920812: added property ROOM_HAS_WATER
 */

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Terel/common/terel_defs.h"

#define BS(message)     break_string(message, 70)

create_room()
{
    set_short("Stone bridge on south road");

    set_long(BS(
        "You are standing on a stone bridge. The river streams rather fast " +
        "and some chunks of ice are passing by. Some trees grow on the " +
        "river banks. The road continues to north and south.\n"));

    add_item(({"tree", "trees"}), BS("These pine trees are all tall and " +
        "straight. Perfect for building cabins and houses.\n"));

    add_item(({"snow"}), BS("The snow never disappears in this part of " +
        "the world. Here it's damn cold unless you have warm clothes.\n"));

    add_item(({"river", "water"}), BS("The river streams fast, otherwise " +
        "it would have been covered with an ice layer. The water is real " +
        "cold.\n"));

    add_item(({"bridge", "stone bridge"}), BS("It's a robust stone bridge " +
        "that will last for many years.\n"));

    add_prop(ROOM_HAS_WATER, 1);

    add_exit(TOWNDIR + "road_s/road_s01", "north", 0);
    add_exit(TOWNDIR + "road_s/road_s03", "south", 0);
}
