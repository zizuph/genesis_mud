/* Modified by dust 920812: added property ROOM_HAS_WATER
 *			correction: added ampty fish() function
 */
// Modified by Lilith, Mar 2022: slight re-map of area, added
//   items and fleshed out descriptions, added fishing.

inherit "std/room";
#include "/d/Terel/common/terel_defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

void
create_room()
{
   set_short("Old Bridge");
   set_long("This long covered wooden bridge stretches across the " +
      "icy waters of the river. The bridge is old, but kept in excellent " +
      "condition. The current of the water is swift. "+
      "A peaceful hush hangs over this place, a welcome "+
      "silence compared to the bustle of the town of Calathin to the north. "+
      "South is the sacred garden.\n");
   
   add_exit("/d/Terel/common/town/garden/entrance", "north", 0);
   add_exit("/d/Terel/common/town/garden/garden1", "south", 0);
   
   add_prop(ROOM_HAS_WATER, 1);	/* you can fill the bucket here */
   add_prop("_live_i_can_fish", ({"freshwater"}));  
   add_prop(ROOM_I_TYPE, ROOM_BEACH);
   
   add_npc("/d/Terel/common/town/garden/fisherman", 1);
   
   add_item(({"bridge", "old bridge"}), "It is very old and made " +
      "of wood. It appears to be in excellent condition.\n");	  
   add_item(({"tree", "trees", "pine trees", "pines", "ancient pines", 
        "ancient pine tress", "ancient trees", "forest", "boughs"}),
    	"These ancient pine trees are all tall and straight, " +
        "with thick trunks that are perfect for building cabins "+
		"and houses. They grow thickly together and cast a deep, "+
        "mysterious shade. Their boughs are covered in snow.\n");
    add_item(({"shade", "deep shade" }), 
      "The ancient pine trees grow so thickly together that they cast a "+
      "mysteriously deep shade over the area.\n");		  
    add_item(({"snow", "ice"}), "The ice and snow never disappears in "+
        "this part of the world. Here it's damn cold unless you have warm clothes.\n");
    add_item(({"river", "water"}), "The river streams fast, otherwise " +
        "it would have been covered with an ice layer. The water is real " +
        "cold. The riverbank is overgrown with various plantlife.\n");
    add_item(({"plantlife","plants","riverbank", "soil", "muddy soil"}),
        "Various plantlife thrive in the frozen muddy soil of the riverbank.\n");	  

   
   
}
