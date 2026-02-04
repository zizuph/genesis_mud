/*
    This is a standard east road. Mortricia 920723
    Updated by Shinto 10-21-98
    	Lilith Mar 2022: updated exits, room desc, etc.
 */

#include "/d/Terel/include/Terel.h"
#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/include/herb_arrs.h"

inherit STDROOM;
inherit "/d/Terel/std/herbsearch.c";

void
create_room()
{
    set_short("The east road");
    set_long(
        "You are in the outskirts of Calathin town, standing on a " +
        "road that runs east-west alongside a river. A row of build"+
        "ings blocks the way north. South is a frosty riverbank "+
        "with some pine trees and lumps of vegetation.\n");

    add_item(({"tree", "trees", "pine trees", "pines"}),
    	"These pine trees are all tall and " +
        "straight. Perfect for building cabins and houses.\n");

    add_item(({"snow"}), "The snow never disappears in this part of " +
        "the world. Here it's damn cold unless you have warm clothes.\n");

    add_item(({"river", "water"}), "The river streams fast, otherwise " +
        "it would have been covered with an ice layer. The water is real " +
        "cold. The riverbank is overgrown with various plantlife.\n");

    add_item(({"plantlife","plants","riverbank", "soil", "muddy soil",
        "vegetation", "lumps of vegetation", "lumps"}),
        "Various plantlife thrive in the muddy soil of the riverbank.\n");

    add_item(({"buildings", "building", "row", "row of buildings"}),
        "You can see the back side of the buildings. From the lively "+
        "sounds coming from the north, you think they are pubs or inns.\n");

   set_up_herbs( ({ one_of_list(RIVER_HERBS),
                    one_of_list(RIVER_HERBS),
                    one_of_list(RIVER_HERBS),					
                 }),
                 ({"plants","riverbank", "plantlife"}) , 
                  3 );

   add_cmd_item(({"river"}),"drink","The riverbank is to steep " +
      "and the river is too swift for you to drink safely from here.\n");


//    add_exit(CALATHIN_DIR + "square1_4", "west", 0);
  add_exit("/d/Terel/common/town/street/street1", "west", 0);  
  add_exit(CALATHIN_DIR + "roads/road_e01", "east", 0);

    reset_room();
}
