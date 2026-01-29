inherit "/d/Shire/common/lib/rom";

#include "defs.h"

create_rom()
{
    set_short("East of the Bree-hill");
    set_long("You are walking towards the 'hill', a famous hill because "
    	    +"of all the hobbits holes there which can be seen from a long "
    	    +"distance. South of here you can see two buildings. The "
    	    +"road goes northwest towards the north gate of Bree, northeast "
          +"towards the Bree-hill and south towards the center of Bree. "+
   "Vibrant fragrances emanate from a new shop to the north.\n");
    	    
    add_item(({"bree hill","bree-hill","hill"}),
    	    "The Bree hill is only a small hill, about 100 feet high. It is "
    	   +"surrounded by a wall and not many trees grow there. But since the "
    	   +"hobbits is such a keen folk, they tend to help things grow. "
    	   +"You can see that by all the nice gardens in Shire.\n");
    	   
    add_item(({"north gate","gate","northern gate","north-gate"}),
            "The gate is closing your view further north. You can see that "
            +"the gate is strong and sturdy, and it would take a lot of power "
            +"to tear it down.\n");
            
    add_exit(BREE_DIR + "nroad1", "northwest", 0, 1);
    add_exit(BREE_DIR + "hill1", "northeast", 0, 2);
   add_exit(BREE_DIR + "ncross","south",0,1);
   add_exit(BREE_DIR + "perfumery","north",0,1);
    
}
