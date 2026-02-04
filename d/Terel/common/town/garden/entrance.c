// Modified by Lilith, Mar 2022: slight re-map of area, added
//   items and fleshed out descriptions, added fishing.

inherit "std/room";
#include "/sys/stdproperties.h"
#define PATH "/d/Terel/common/town/"

void
create_room(){
   set_short("River's Edge");
   set_long("The riverbank is frozen and coated with a " +
      "sheet of ice, making the river dangerous to get near. " +
      "A peaceful hush hangs over this place, a welcome "+
      "silence compared to the bustle of town. "+
      "An old wooden bridge spans south across the river, beyond " +
      "it on the other side of the river are many trees. A paved " +
      "cobblestone street runs northeast from here.\n");
   
   add_exit(PATH + "garden/bridge", "south", 0);
   add_exit(PATH + "street/street2", "northeast", 0);

   add_prop("_live_i_can_fish", ({"freshwater"}));  
   add_prop(ROOM_I_TYPE, ROOM_BEACH);
   
   add_item(({"bridge", "old bridge"}), "It is very old and made " +
      "of wood.\n");	  
   add_item(({"tree", "trees", "pine trees", "pines", "ancient pines", 
        "ancient pine tress", "ancient trees", "boughs"}),
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
