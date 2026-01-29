inherit "/d/Gondor/common/room";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/pelargir/citdefs.h"

void
create_room()
{
    set_short("on an east-west road");
    set_long(BSN("This is one of the cobblestone streets of "+
       "Pelargir. The street leads from the docks in the east to the "+
       "towering statue in the city square west of here. To the "+
       "south are some poor quality buildings, and to the north is some "+
       "kind of shop."));
    COBBLE;
    GADMIRAL;
    add_item("statue",BSN("The statue is rather tall and bulky but "+
       "other than that you can't see details without getting "+
       "closer."));
    add_item("shop",BSN("The large stone building has "+
       "the single word 'MASON' delicately chipped into it "+
       "above the door."));
    add_exit(PELAR_DIR + "street/sroad2","east",0);
    add_exit(PELAR_DIR + "street/statue","west",0);
    add_exit(PELAR_DIR + "misc/pelstone","north",0);
}
