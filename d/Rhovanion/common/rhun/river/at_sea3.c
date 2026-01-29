
inherit "/d/Rhovanion/lib/room";
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/farlong.h"

void
create_room()
{
    set_short("On the Sea of Rhun");
    set_long(break_string("You are sailing into the Sea of Rhun."
	+"  Only water can be seen all around you as the"
	+" ship plunges onward toward"
	+" the sea's center.\n",75));
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
