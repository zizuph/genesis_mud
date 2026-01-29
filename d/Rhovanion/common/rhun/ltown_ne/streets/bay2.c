#pragma save_binary

inherit "/d/Rhovanion/lib/room";
#include "/sys/stdproperties.h"

void create_room()
{
  set_short("Out on the Sea of Rhun");
  set_long("The Sea of Rhun"
	+" stretches off all around you.  You can see the"
	+" shore to the north, and also the place where"
	+" the River Carnen empties into the sea.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}