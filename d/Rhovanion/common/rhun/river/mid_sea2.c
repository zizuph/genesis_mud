
inherit "/d/Rhovanion/lib/room";
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/farlong.h"

void
create_room()
{
    set_short("Middle of the Sea");
    set_long(break_string("The ship's path here heads from east to"
	+" west.  Westward you can make out a small beach, while"
	+" deeper waters lie to the east.\n",75));
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
