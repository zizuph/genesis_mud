
inherit "/d/Rhovanion/lib/room";
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/farlong.h"

void
create_room()
{
    set_short("Middle of the Sea");
    set_long(break_string("You are out near the center of the Sea"
	+" of Rhun.  There is nothing but heaving, thrashing water all"
	+" around you.  You wonder if the captain really knows where he's"
	+" going.\n",75));
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
