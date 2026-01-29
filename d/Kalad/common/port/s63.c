#include "default.h"
inherit PORT_ROOM;

void
create_port_room()
{
    add_prop(ROOM_I_INSIDE,1);
    set_short("Warehouse");
    set_long("This large wooden enclosure is the interior of one of the "+
      "port district warehouses. The only light comes from several windows "+
      "high up in the southern wall. All about you are a myriad number of "+
      "large wooden crates, each bearing the same symbol.\n");
    add_item(({"several windows","windows","window"}),"Small, narrow windows that "+
      "let in a minimum of light.\n");
    add_item(({"large wooden crates","large crates","wooden crates","crates","crate"}),
      "From the size of the containers, you estimate their weight to be in the "+
      "hundreds of pounds. Each one bears a mark, indicating which company or group "+
      "it belongs to.\n");
    add_item(({"symbol","mark"}),"An image of a golden coin with rays of light emanating from it "+
      "has been placed on each crate.\n");
    add_item(({"southern wall","wall"}),"It holds up the warehouse.\n");
    add_exit(PORT + "s76", "south");
}

