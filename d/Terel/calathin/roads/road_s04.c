/*
    This is a standard south road. Mortricia 920728
    Updated by Shinto 10-21-98
  */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

#include <stdproperties.h>
#include <macros.h>

object guard;

void
reset_room()
{
    if (guard)return;
    guard = clone_object(CALATHIN_DIR + "npc/std_move_guard");
    guard -> move_living("xx",TO);
   
}

public void
create_room()
{
    set_short("The south road");

    set_long(
        "This icy road will take you to the southern parts of Calathin. " +
        "There are a few trees scattered around the road. " +
        "The road continues to the northwest and to the south.\n");

    add_item(({"tree", "trees"}), "These pine trees are all tall and " +
        "straight. Perfect for building cabins and houses.\n");

    add_item(({"snow"}), "The snow never disappears in this part of " +
        "the world. Here it's damn cold unless you have warm clothes.\n");

    add_exit(CALATHIN_DIR + "roads/road_s03", "northwest", 0);
    add_exit(CALATHIN_DIR + "roads/road_s05", "south", 0);

    reset_room();
}
