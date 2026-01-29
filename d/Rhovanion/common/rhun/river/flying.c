inherit "/d/Rhovanion/lib/room";

#include "/sys/stdproperties.h"

void
create_room()
{
    set_short("Flying through the air");
    set_long("The dragon is flying so fast that you can't make anything "+
          "of the land below.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
