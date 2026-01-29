inherit "/d/Shire/common/lib/rom";
#include "/d/Shire/common/defs.h"

#include "defs.h"

create_rom()
{
    set_short("West road of Bree.");
    set_long("This street meanders westwardly through the human parts of "+
    "Bree. The houses around here are not quite as nice as the ones farther "+
    "west, but they have gardens. North and south are houses, and to the "+
    "east, the road to Deadman's Dike begins. The street continues "+
    "west.\n");
    	    
    
    add_item(({"street","road","ground","here"}), "The road "+
    "here leads west to the outer parts of Bree, and east is "+
    "the junction with the road to Deadman's Dike.\n");

    add_item(({"south house","southern house","window","windows"}),
    "Looking at the windows, you notice that one of the ones in "+
    "the house south of here is broken out.\n");

    add_item(({"house","houses","garden","gardens"}), "The houses "+
    "here have gardens that are not entirely neglected, and the "+
    "houses themselves are mostly made of wood, with stone foundations. "+
    "Some of them even have windows.\n");

   add_exit(BREE_DIR + "brroad1","east",0,2);
   add_exit(BREE_DIR + "wroad2","west",0,2);
    add_exit(BREE_DIR + "hhouse2","south",0,1);
}
