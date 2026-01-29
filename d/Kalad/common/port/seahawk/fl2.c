#include "../default.h"
inherit PORT_ROOM;

void
create_port_room()
{
    set_short("Main corridor of Lower Level");
    set_long("This is the main corridor of the Seahawk's lower level. "+
      "To the east, you can see a flight of stairs, and to the north "+
      "and south there appear to be small rooms.\n");
    add_item(({"flight of stairs","flight","stairs"}),"A set of wooden "+
      "steps that leads up to the ship's upper deck.\n");
    add_item(({"main corridor","corridor"}),"The narrow passage continues "+
      "to the west and east.\n");
    add_item(({"small rooms","rooms","room"}),"Side chambers that look "+
      "to be the residence of the ship's crew, back in the days when the "+
      "Seahawk was free to roam the sea.\n");

    add_prop(ROOM_I_INSIDE,1);

    add_exit(PORT + "seahawk/fl6", "west");
    add_exit(PORT + "seahawk/fl3", "north");
    add_exit(PORT + "seahawk/fl1", "east");
    add_exit(PORT + "seahawk/fl4", "south");
}

