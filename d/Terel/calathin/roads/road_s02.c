/*
    This is a standard east road. Mortricia 920723
    Modified by dust 920812: added property ROOM_HAS_WATER
    Updated by Shinto 10-21-98
  */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

#include <stdproperties.h>
#include <macros.h>


public void
create_room()
{
    set_short("Stone bridge on south road");

    set_long(
        "You are standing on a stone bridge. The river streams rather fast " +
        "and some chunks of ice are passing by. Some trees grow on the " +
        "river banks. The road continues to north and south.\n");

    add_item(({"tree", "trees"}), "These pine trees are all tall and " +
        "straight. Perfect for building cabins and houses.\n");

    add_item(({"snow"}), "The snow never disappears in this part of " +
        "the world. Here it's damn cold unless you have warm clothes.\n");

    add_item(({"river", "water"}), "The river streams fast, otherwise " +
        "it would have been covered with an ice layer. The water is real " +
        "cold.\n");

    add_item(({"bridge", "stone bridge"}), "It's a robust stone bridge " +
        "that will last for many years.\n");

    add_prop(ROOM_HAS_WATER, 1);

    add_exit(CALATHIN_DIR + "roads/road_s01", "north", 0);
    add_exit(CALATHIN_DIR + "roads/road_s03", "south", 0);
    add_exit(CALATHIN_DIR + "tunnel/tunnel_s06", "down", 0, 1, 1);
}
