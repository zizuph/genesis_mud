#include "../default.h"
inherit PORT_ROOM;

void
create_port_room()
{
    set_short("This is the far end of the corridor");
    set_long("This is the far end of the corridor. From here the rest "+
      "of the passage continues eastward, while side rooms lie just to the "+
      "north and south. A small sign hangs on the wall.\n");
    add_item(({"corridor","passage"}),"A narrow hallway from which "+
      "there are exits leading to several side rooms. Two such exits lie "+
      "north and south from here.\n");
    add_item(({"side rooms","rooms","room"}),"Small chambers that lie "+
      "off of the corridor.\n");
    add_item("sign","@@sign");
    add_cmd_item("sign","read","@@sign");

    add_prop(ROOM_I_INSIDE,1);

    add_exit(PORT + "seahawk/fl8", "north");
    add_exit(PORT + "seahawk/fl6", "east");
    add_exit(PORT + "seahawk/fl10", "south");
}

sign()
{
    return "Captain's Cabin: South\n"+
    "First Mate's Cabin: North\n";
}

