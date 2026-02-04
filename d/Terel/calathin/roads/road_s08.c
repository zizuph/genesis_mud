/*
    This is a standard south road. Mortricia 920723
    Updated by Shinto 10-21-98
  */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;


#include <stdproperties.h>
#include <macros.h>

public void
create_room()
{
    set_short("The southern road");

    set_long(
        "This icy road will take you to the southern parts of Calathin. " +
        "There are a few trees scattered around the road. " +
        "The road continues north and south. Far south you " +
        "see a large forest.\n");

    add_item(({"tree", "trees"}), "These pine trees are all tall and " +
        "straight. Perfect for building cabins and houses.\n");

    add_item(({"snow"}), "The snow never disappears in this part of " +
        "the world. Here it's damn cold unless you have warm clothes.\n");
    add_item(({"forest"}), "The forest must be quite extended, "+
     "since it reaches almost over the whole southern horizon, but " +
     "that is about all you can figure out from here.\n");

    add_exit(CALATHIN_DIR + "roads/road_s07", "north", 0);
    add_exit(CALATHIN_DIR + "roads/road_s09", "south", 0);
}
