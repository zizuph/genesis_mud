#include "defs.h"
inherit STD_ROOM;

string suffix = "";

void
create_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    ::create_room();
    set_short("Within a misty cavern");
    set_long(
      "You are in a dark cavern, bathed in a spectral mist. There is little " +
      "to see but stone columns." +
      suffix + "\n");
    add_item(({"column", "stone column", "columns", "stone columns"}),
      "Columns of black stone seem to support the cavern, but the mist " +
      "prevents you from seeing above.\n");
    add_item(({"mist", "spectral mist"}),
      "The mist floats around the area like ghostly spirits.\n");
    add_prop(ROOM_I_LIGHT, 0);
}
