inherit "/d/Gondor/common/room";

#include "/sys/stdproperties.h"

#include "/d/Gondor/defs.h"
#include "/d/Gondor/pelargir/citdefs.h"

void
create_room()
{
    set_short("on an east-west road");
    set_long(BSN("This stretch of road seems to be kept in good "+
       "repair, probably due to the barracks north of here. "+
       "There do not seem to be too many travellers on this road, but "+
       "the only thing of interest on the east end is the lighthouse "+
       "unless one feels like going swimming."));
    add_item("barracks",BSN("The barracks do not seem nearly "+
       "big enough to house the entire city guard. Perhaps it is "+
       "just one of many barracks throughout the city."));
    COBBLE;
    NORTHSIDE;
    NADMIRAL;
    NLIGHTH;
    add_exit(PELAR_DIR + "street/nroad2","west",0);
    add_exit(PELAR_DIR + "street/nroad4","east",0);
}
