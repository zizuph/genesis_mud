// Sea in the underground ocean.
//   -Cirion, 1997
inherit "/std/room";

#include "../ship.h"

void
create_room()
{
    set_short("dark sea");
    set_long("Rising up to the east is the breathtaking eastern "
      + "face of sybarus cavern. The ship is near a wide, "
      + "stone ledge that leads into the tunnel.\n");

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

}
