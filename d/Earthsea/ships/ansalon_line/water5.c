inherit "/d/Earthsea/std/room";

#include "defs.h"
#include "/sys/stdproperties.h"

void
create_earthsea_room()
{
    set_short("On the sea");
    set_long("The bloody red sea of Ansalon surrounds the "+
      "ship. You see the port of Balifor not far away.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
