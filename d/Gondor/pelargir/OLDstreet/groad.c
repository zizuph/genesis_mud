inherit "/d/Gondor/common/room";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/pelargir/citdefs.h"

void
create_room()
{
    set_short("North/South Pelargir street");
    set_long(BSN("You are on a fine cobblestone street heading "+
       "north and south through the city of Pelargir. To the west, "+
       "all the houses are of high quality, while to the east you can "+
       "see the side of the stone mason's workshop and the Admiral's "+
       "giant white tower. The statue to the south marks the "+
       "square of Pelargir."));
   COBBLE;
   GADMIRAL;
   add_item("houses",BSN("These houses are some of the oldest in "+
      "Pelargir. The care and delicate worksmanship that "+
      "was put into building them is obvious in the finely "+
      "crafted stone walls and pillars."));
   add_item(({"mason's workshop","workshop"}),BSN("The "+
      "mason's workshop is very plain looking. It is probable from "+
      "the size, shape and care of the shop, that it was "+
      "built with the sole intention of lasting forever."));
   add_item("statue",BSN("Perhaps going on into the square "+
      "would afford a better look."));
    add_exit(PELAR_DIR + "street/groad1","north",0);
    add_exit(PELAR_DIR + "street/statue","south",0);
}
