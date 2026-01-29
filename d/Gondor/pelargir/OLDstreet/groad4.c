inherit "/d/Gondor/common/room";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/pelargir/citdefs.h"

void
create_room()
{
    set_short("North/South Pelargir street");
    set_long(BSN("You are standing at the base of a stone "+
       "bridge over the Sirith River. The bridge looks to have stood "+
       "there for many years, but shows little signs of wear. To the "+
       "south the street continues on through Pelargir, and past the "+
       "Admiral's Tower which looms high above the rooftops. To the "+
       "northeast you can step out onto the bridge."));
    COBBLE;
    NADMIRAL;
    add_item("bridge",BSN(
       "The aged bridge spans the Sirith river to the "+
       "north and leads towards the city gates and lighthouse."));
    add_item(({"river","sirith"}),BSN(
      "The river Sirith runs under the stone bridge, and the current "+
      "looks fairly strong here as this is a more narrow "+
      "part than elsewhere."));
    add_exit(PELAR_DIR + "street/bridstone","northeast",0);
    add_exit(PELAR_DIR + "street/groad3","south",0);
}
