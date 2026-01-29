
inherit "/d/Rhovanion/lib/room";
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/farlong.h"

void
create_room()
{
    set_short("On the Sea of Rhun");
    set_long(break_string("The flat beaches have passed away, and"
	+" now you press onward into the Sea of Rhun, challenging the"
	+" waves that continute to press at the ship's sides.\n",75));
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
