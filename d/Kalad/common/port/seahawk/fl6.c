#include "../default.h"
inherit PORT_ROOM;

void
create_port_room()
{
    set_short("Main corridor of Lower Level");
    set_long("This is a section of the main corridor of the Seahawk's "+
      "lower level. The area is devoid of activity, however, above and "+
      "below you are sounds indicating the presence of someone, or "+
      "some thing.\n");
    add_item(({"section","main corridor","corridor"}),"The narrow "+
      "passageway continues to the west and east, with side rooms to the "+
      "north and south.\n");
    add_item(({"side rooms","rooms","room"}),"Most likely one of the "+
      "former residences of the Seahawk's crew.\n");

    add_prop(ROOM_I_INSIDE,1);

    add_exit(PORT + "seahawk/fl9", "west");
    add_exit(PORT + "seahawk/fl5", "north");
    add_exit(PORT + "seahawk/fl2", "east");
    add_exit(PORT + "seahawk/fl7", "south");
}

