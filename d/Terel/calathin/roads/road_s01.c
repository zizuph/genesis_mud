/*
    This is a standard east road. Mortricia 920723
    Updated by Shinto 10-21-98
  */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

#include <stdproperties.h>
#include <macros.h>

public void
create_room()
{
    set_short("The south road");

    set_long(
        "This icy road will take you to the southern parts of Calathin. " +
        "You are standing on the northern bank of a river. " +
        "There are a few trees scattered around the road. " +
        "To the northwest this road reaches a somewhat larger road. " +
        "You can walk on the stone bridge by going south.\n");

    add_item(({"tree", "trees"}), "These pine trees are all tall and " +
        "straight. Perfect for building cabins and houses.\n");

    add_item(({"snow"}), "The snow never disappears in this part of " +
        "the world. Here it's damn cold unless you have warm clothes.\n");

    add_item(({"river", "water"}), "The river streams fast, otherwise " +
        "it would have been covered with an ice layer. The water is real " +
        "cold.\n");

    add_item(({"bridge", "stone bridge"}), "It's a robust stone bridge " +
        "that will last for many years.\n");

    add_exit(CALATHIN_DIR + "south_gate","north",0);
    add_exit(CALATHIN_DIR + "roads/road_s02", "south", 0);
}
