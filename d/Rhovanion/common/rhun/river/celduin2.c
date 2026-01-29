
inherit "/d/Rhovanion/lib/room";
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/farlong.h"

void
create_room()
{
    set_short("On the River Celduin");
    set_long(break_string("You are travelling along the River Running."
	+"  It flows from east to west here.  North and south of"
	+" the riverbank, only the vast, empty, and mostly-unexplored"
	+" plains of western Rhun extend."
	+"\n",75));
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
