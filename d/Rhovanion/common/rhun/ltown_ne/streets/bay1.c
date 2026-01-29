#pragma save_binary

inherit "/d/Rhovanion/lib/room";
#include "/sys/stdproperties.h"

void create_room()
{
  set_short("Out on the Sea of Rhun");
  set_long("You are out on the Sea of Rhun, travelling"
	+" across the bay on its northwestern corner, where the River"
	+" Carnen arrives from the north.  The salty water lies all"
	+" around you, lapping at the boat's sides.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}