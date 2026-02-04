/*
    This is a standard east road. Mortricia 920723
    Updated by Shinto 10-21-98
  */

#include "/d/Terel/include/Terel.h"
#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/include/herb_arrs.h"

inherit STDROOM;
inherit "/d/Terel/std/herbsearch.c";

#define  ONE_OF_LIST(array) ((array)[random(sizeof(array))])


public void
create_room()
{
    set_short("The east road");

    set_long(
        "This icy and snowy road will take you eastwards. There are some " +
        "trees here and there. There are some bushes to the north. " +
        "The road goes along a river.\n");

    add_item(({"tree", "trees"}), "These pine trees are all tall and " +
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

   add_cmd_item(({"from river","river"}),"drink","The riverbank is to steep " +
      "and the river is too swift for you to drink safely from here.\n");
        
    add_item(({"thorn", "bushes", "thorns"}), "The thorn-bushes seem " +
             "very thick. You doubt something can be hidden there.\n");

    add_exit(CALATHIN_DIR + "roads/road_e08", "west", 0);
    add_exit(CALATHIN_DIR + "roads/road_e10", "east", 0);

    reset_room();
}
