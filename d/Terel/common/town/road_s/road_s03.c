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
        "This icy road will take you to the southernmost parts of Calathin. " +
        "You are standing on the southern river bank, and north is a " +
        "stone bridge.  A small path leads east into the forest.\n"));

    add_item(({"tree", "trees"}), BS("These pine trees are all tall and " +
        "straight. Perfect for building cabins and houses.\n"));

    add_item(({"snow"}), BS("The snow never disappears in this part of " +
        "the world. Here it's damn cold unless you have warm clothes.\n"));

    add_item(({"river", "water"}), BS("The river streams fast, otherwise " +
        "it would have been covered with an ice layer. The water is real " +
        "cold.\n"));

    add_item(({"bridge", "stone bridge"}), BS("It's a robust stone bridge " +
        "that will last for many years.\n"));

    add_exit(TOWNDIR + "road_s/road_s02", "north", 0);
    add_exit(TOWNDIR + "road_s/road_s04", "southeast", 0);
    add_exit(TOWNDIR + "road_s/p_guild_1", "east", 0);
}
