inherit "/d/Shire/common/lib/rom";
#include "/d/Shire/common/defs.h"

#include "defs.h"

create_rom()
{
    set_short("North road of Bree");
    set_long("The road leading north to Deadman's Dike begins here. "+
    "The road bends north through some marshes and to the south and east "+
    "you see the Bree hill. "+
    "The houses around here are all those of humans, and you notice "+
    "they have much fewer gardens than hobbits. North you can see "+
    "a small outbuilding near the gate and to the south you can enter a "+
    "house.\n");
    	    
    
    add_item("marshes", "A bit difficult to see anything behind this tall gate?\n");
   add_item(({"hill","hills","road","path"}), "You are "+
   "standing near the top of the Bree-Hill, though this is the "+
   "northwest corner, the main hill is southeast of here, you can "+
   "even take the road there.\n");
   add_item(({"bushes","bush","shrubs"}), "The shrubbery around here is "+
   "quite dense and overgrown. Upon closer examination, however, you "+
   "think you see an owl in one of the bigger bushes.\n");

   add_item("owl","Ah, it's not an owl, only a dead part of the bush.\n");

    add_item(({"house","houses","garden","gardens"}), "The houses "+
    "of humans are not strictly one story as are hobbit dwellings, "+
    "the house to the south you can enter.\n");

    add_item(({"outbuilding","gate"}),"The Gatekeeper's lodge "+
    "is to the north. There the gates of Bree are kept, open during the "+
    "day and closed at night.\n");
   add_exit(BREE_DIR + "brroad1","southeast",0,2);
   add_exit(BREE_DIR + "northgate","north",0,2);
    add_exit(BREE_DIR + "hhouse1","south",0,1);
}
