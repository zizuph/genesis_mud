/*
    This is a standard east road. Mortricia 920723
    Updated by Shinto 10-21-98

    Modified: 3 May 2003, by Bleys
        - fixed a typo
  */

#include "/d/Terel/include/Terel.h"
#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/include/herb_arrs.h"

inherit STDROOM;
inherit "/d/Terel/std/herbsearch.c";

#define  ONE_OF_LIST(array) ((array)[random(sizeof(array))])


object guard, guard1;

void
reset_room()
{

    if(guard) return;
    guard = clone_object(CALATHIN_DIR + "npc/std_guard");
    guard -> move_living("xx",TO);
    
    if(guard1) return;
    guard1 = clone_object(CALATHIN_DIR + "npc/std_guard");
    guard1 -> move_living("xx",TO);

    return;
}

create_room()
{
    set_short("The east road");

    set_long(
        "This icy and snowy road will take you eastwards. There are some " +
        "trees here and there. The road goes along a river.\n");

    add_item(({"tree", "trees"}),"These pine trees are all tall and " +
        "straight. Perfect for building cabins and houses.\n");

    add_item(({"snow"}), "The snow never disappears in this part of " +
        "the world. Here it's damn cold unless you have warm clothes.\n");

    add_item(({"river", "water"}), "The river streams fast, otherwise " +
        "it would have been covered with an ice layer. The water is real " +
        "cold. The riverbank looks quite steep and filled with various " +
        "plantlife.\n");

    add_item(({"plantlife","plants","riverbank"}),
        "Various plantlife thrive in the muddy soil of the riverbank.\n");

   set_up_herbs( ({ ONE_OF_LIST(RIVER_HERBS),
                    ONE_OF_LIST(RIVER_HERBS),
                    ONE_OF_LIST(RIVER_HERBS),
                 }),
                 ({"plants","riverbank", "plantlife"}) , 
                  3 );

   add_cmd_item(({"from river","river"}),"drink","The riverbank is too steep " +
      "and the river is too swift for you to drink safely from here.\n");

    add_prop(ROOM_HAS_WATER, 1);

    add_exit(CALATHIN_DIR + "in_east_gate", "east",0);
    add_exit(CALATHIN_DIR + "roads/road_e15", "northwest", 0);

    reset_room();
}
