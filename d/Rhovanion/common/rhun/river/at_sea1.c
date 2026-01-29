
inherit "/d/Rhovanion/lib/room";
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/farlong.h"

void
create_room()
{
    set_short("On the Sea of Rhun");
    set_long(break_string("You are sailing into the Sea of Rhun."
	+"  Waves lap at the ship's sides as it presses onward."
	+"  Off to the northeast and southwest, large towns stand"
	+" on the water's edges.\n",75));
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
