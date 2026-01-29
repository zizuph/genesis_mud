inherit "/d/Gondor/common/room";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/pelargir/citdefs.h"

void
create_room()
{
    set_short("on an east-west road");
    set_long(BSN("This road forms a dividing line between the "+
       "poor section and the rest of Pelargir. The road leads east-"+
       "west with the docks to the east and the city square to the "+
       "west. To the south a small side street leads into the poor "+
       "section where it takes a sharp turn. North lie some "+
       "of the common housing buildings of Pelargir (all locked)."));
       add_item(({"houses","buildings"}),BSN("These are all "+
          "bolted from the inside; it seems the people of "+
          "Pelargir just do not trust all the visitors of late."));
       COBBLE;
    add_exit(PELAR_DIR + "street/sroad","east",0);
    add_exit(PELAR_DIR + "street/proad","south",0);
    add_exit(PELAR_DIR + "street/sroad2","west",0);
}
