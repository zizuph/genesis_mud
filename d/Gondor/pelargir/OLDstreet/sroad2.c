inherit "/d/Gondor/common/room";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/pelargir/citdefs.h"

void
create_room()
{
    set_short("on an east-west road");
    set_long(BSN("You are on one of the main roads in "+
       "Pelargir. To the south the poorer section of Pelargir "+
       "lies between this street and the city wall. North of this "+
       "street, the city spreads out before you, though it is mostly "+
       "homes of loyal Pelargir citizens. Down the road to the west "+
       "you can see a huge statue of some sort in the city square. "+
       "To the east, you can only assume the docks rest along the "+
       "Anduin river's edge."));
   COBBLE;
   GADMIRAL;
   add_item("statue",BSN("The statue is too far away to "+
          "get a very good look."));
   add_item("homes",BSN("To the south the houses are of much poorer "+
          "quality than those to the north."));
    add_exit(PELAR_DIR + "street/sroad1","east",0);
    add_exit(PELAR_DIR + "street/sroad3","west",0);
}
