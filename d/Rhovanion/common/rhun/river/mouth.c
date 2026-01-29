
inherit "/d/Rhovanion/lib/room";
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/farlong.h"

void
create_room()
{
    set_short("Mouth of river");
    set_long(break_string("This is the mouth of the River Carnen,"
	+" as it flows southeastward into the vastness of the"
	+" Sea of Rhun.\n",75));
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
