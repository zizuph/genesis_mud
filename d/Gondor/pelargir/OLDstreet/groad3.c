inherit "/d/Gondor/common/room";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/pelargir/citdefs.h"

void
create_room()
{
    set_short("North/South Pelargir street");
    set_long(BSN("This is a crossing of two cobblestone "
      + "streets in Pelargir. The main road leads north to "
      + "a bridge over the Sirith River, and south to the "
      + "busier parts of Pelargir. The secondary road leads "
      + "to a smattering of houses to the east and the "
      + "wealthy section of Pelargir to the west. The Admiral's "
      + "white tower looms tall above the buildings in the "
      + "southeast."));
     COBBLE;
     add_item(({"bridge","houses","wealthy section"}),BSN("If "+
        "you were closer, you could get a better look."));
     NADMIRAL;
    add_exit(PELAR_DIR + "street/groad4","north",0);
    add_exit(PELAR_DIR + "street/groad2","south",0);
    add_exit(PELAR_DIR + "street/xroad","east",0);
    add_exit(PELAR_DIR + "street/xroad2","west",0);
}
