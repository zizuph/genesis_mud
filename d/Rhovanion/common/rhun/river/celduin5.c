
inherit "/d/Rhovanion/lib/room";
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/farlong.h"

void
create_room()
{
    set_short("At the south side of Long Lake, north end of the River "
	+"Celduin.\n");
    set_long(break_string("You are on a wooden ship, travelling by"
	+" the intersection of the River Celduin (often called the"
	+" River Running) and Long Lake.  North, Esgaroth lies at the"
	+" center of the lake, a city of wood on its watery surface."
	+"\n",75));
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
