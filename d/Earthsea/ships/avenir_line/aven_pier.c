inherit "/d/Earthsea/std/room";

#include "/sys/stdproperties.h"

// Temporary pier with endpoint in Avenir
void
create_earthsea_room()
{
    set_short("Stone Pier");
    set_long("You are standing on a long stone pier that "+
      "extends out into the bay.\n");
    add_prop(ROOM_I_IS, 1);
    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_INSIDE, 0);
}
